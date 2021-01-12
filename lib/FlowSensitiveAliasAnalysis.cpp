#include "FlowSensitiveAliasAnalysis.h"
#include "AliasGraph/AliasGraph.h"
#include "AliasToken/Alias.h"
#include "AliasToken/AliasToken.h"
#include "CFGUtils/CFGUtils.h"
#include "DemandDrivenAliasAnalysisDriver.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "set"
#include "stack"

using namespace llvm;
using namespace FlowSensitiveAA;
using AliasMap = AliasGraphUtil::AliasGraph<AliasUtil::Alias>;

void PointsToAnalysis::handleGlobalVar(llvm::Module& M) {
    // Handle global variables
    for (auto& G : M.getGlobalList()) {
        auto Aliases = AT->extractAliasToken(&G);
        auto Redirections = AT->extractStatementType(&G);
        if (Aliases.size() == 2) {
            GlobalAliasMap.insert(Aliases[0], Aliases[1], Redirections.first,
                                  Redirections.second);
            // Handle the case when a global variable is initialized
            // with an address
            if (llvm::GlobalVariable* Constant =
                    llvm::dyn_cast<GlobalVariable>(G.getInitializer())) {
                GlobalAliasMap.insert(Aliases[0], AT->getAliasToken(Constant),
                                      2, 1);
            }
        }
    }
}
void PointsToAnalysis::handleCallReturn(llvm::Instruction* Inst) {
    AliasOut[Inst] = AliasIn[Inst];
    auto Aliases = AT->extractAliasToken(Inst);
    if (CallInst* CI = dyn_cast<CallInst>(Inst)) {
        Function& Func = *CI->getCalledFunction();
        // handle return value
        if (!CI->doesNotReturn()) {
            if (ReturnInst* RI = dyn_cast<ReturnInst>(&(Func.back().back()))) {
                auto CallAliases = AT->extractAliasToken(RI);
                if (CallAliases.size() == 1) {
                    AliasOut[&(Func.back().back())].insert(
                        Aliases[0], CallAliases[0], 1, 1);
                }
            }
        }
        // handle change made to globals
        for (auto P : AliasOut[&Func.back().back()]) {
            if (!P.first->sameFunc(&Func)) {
                for (auto X : P.second) {
                    if (!X->sameFunc(&Func)) AliasOut[Inst].insert(P.first, X);
                }
            }
        }
    }
}
void PointsToAnalysis::initializeWorkList(llvm::Module& M) {
    for (Function& F : M.functions()) {
        for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
            if (I == inst_begin(F)) {
                WorkList->push(&*I);
            }
        }
    }
}
bool PointsToAnalysis::isInDemandOut(AliasUtil::Alias* A,
                                     llvm::Instruction* Inst) {
    std::stack<AliasUtil::Alias*> St;
    St.push(A);
    while (!St.empty()) {
        auto Temp = St.top();
        St.pop();
        if (DA->inDemandOut(Temp, Inst)) return true;
        auto Pointee = AliasOut[Inst].getPointee(Temp);
        for (auto X : Pointee) St.push(X);
    }
    return false;
}
void PointsToAnalysis::runAnalysis(llvm::Instruction* Inst) {
    llvm::BasicBlock* ParentBB = Inst->getParent();
    llvm::Function* ParentFunc = ParentBB->getParent();
    std::vector<AliasMap> Predecessors;
    // Handle function arguments
    AliasMap ArgAliasMap;
    for (auto Arg = ParentFunc->arg_begin(); Arg != ParentFunc->arg_end();
         Arg++) {
        auto Aliases = AT->extractAliasToken(Arg, ParentFunc);
        if (Aliases.size() == 2)
            ArgAliasMap.insert(Aliases[0], Aliases[1], 1, 0);
    }
    // Only calculate aliases for global variables and arguments at
    // the
    // start of the function
    if (&ParentBB->front() == Inst) {
        Predecessors.push_back(GlobalAliasMap);
        Predecessors.push_back(ArgAliasMap);
    }
    // Calculate control flow predecessor
    for (Instruction* I : CFGUtils::GetPred(Inst)) {
        if (AliasOut.find(I) != AliasOut.end())
            Predecessors.push_back(AliasOut[I]);
    }
    AliasIn[Inst].merge(Predecessors);
    AliasOut[Inst] = AliasIn[Inst];
    // Extract alias tokens from the instruction
    auto Aliases = AT->extractAliasToken(Inst);
    // Check if the instruction is present in demand
    if (!isa<AllocaInst>(Inst) && !isa<CallInst>(Inst)) {
        bool InDemand = false;
        for (auto X : Aliases) {
            InDemand |= isInDemandOut(X, Inst);
        }
        if (!InDemand) {
            if (&ParentBB->back() == Inst) {
                for (auto C : this->CallGraph[ParentFunc]) {
                    this->handleCallReturn(C);
                }
            }
        }
    }
    // Handle killing
    if (StoreInst* SI = dyn_cast<StoreInst>(Inst)) {
        if (Aliases.size() == 2) {
            auto Pointee = AliasOut[Inst].getPointee(Aliases[0]);
            if (Pointee.size() == 1) {
                auto KillNode = *(Pointee.begin());
                AliasOut[Inst].erase(KillNode);
            }
        }
    }
    // Handle special cases:
    // Handle GEP instructions
    if (GetElementPtrInst* GEP = dyn_cast<GetElementPtrInst>(Inst)) {
        for (auto A : AliasOut[Inst].getPointee(Aliases[1])) {
            AliasUtil::Alias* FieldVal = new AliasUtil::Alias(A);
            FieldVal->setIndex(GEP);
            FieldVal = AT->getAliasToken(FieldVal);
            AliasOut[Inst].insert(Aliases[0], FieldVal, 1, 0);
        }
        // clear Aliases to avoid confusions
        Aliases.clear();
    }
    // handle function call
    if (CallInst* CI = dyn_cast<CallInst>(Inst)) {
        if (!CI->isIndirectCall()) {
            Function& Func = *CI->getCalledFunction();
            if (!CFGUtils::SkipFunction(Func)) {
                // Check if the call is in demand
                if (DA->getDemandOut(&(Func.back().back())).size() != 0) {
                    // pass alias information
                    AliasIn[&(Func.front().front())].merge(
                        std::vector<AliasMap>{AliasIn[Inst]});
                    // handle pass by reference
                    int ArgNum = 0;
                    for (Value* Arg : CI->args()) {
                        AliasUtil::Alias* ActualArg =
                            AT->getAliasToken(new AliasUtil::Alias(Arg));
                        AliasUtil::Alias* FormalArg = AT->getAliasToken(
                            new AliasUtil::Alias(Func.getArg(ArgNum)));
                        AliasIn[&(Func.front().front())].insert(
                            FormalArg, ActualArg, 1, 1);
                        ArgNum += 1;
                    }
                    this->WorkList->push(&(Func.front().front()));
                    this->CallGraph[&Func].insert(Inst);
                    this->handleCallReturn(Inst);
                }
            }
        }
    }
    if (&ParentBB->back() == Inst) {
        for (auto C : this->CallGraph[ParentFunc]) {
            this->handleCallReturn(C);
        }
    }
    // Find the relative redirection between lhs and rhs
    // example for a = &b:(1, 0)
    auto Redirections = AT->extractStatementType(Inst);
    if (Aliases.size() == 2) {
        // Default behavior is copy ie (1, 1)
        // for heap address in RHS make sure it is (x, 0)
        if (Aliases[1]->isMem()) Redirections.second = 0;
        AliasOut[Inst].insert(Aliases[0], Aliases[1], Redirections.first,
                              Redirections.second);
    }
    // Evaluate precision
    auto BenchVar = Bench.extract(Inst);
    if (BenchVar.size() == 2) {
        Bench.evaluate(
            Inst, AliasOut[Inst].getPointee(AT->getAliasToken(BenchVar[0])),
            AliasOut[Inst].getPointee(AT->getAliasToken(BenchVar[1])));
    }
}
std::set<AliasUtil::Alias*> PointsToAnalysis::getAliasOut(
    AliasUtil::Alias* A, llvm::Instruction* Inst) {
    std::set<AliasUtil::Alias*> Pointee;
    if (AliasOut.find(Inst) == AliasOut.end()) return Pointee;
    Pointee = AliasOut[Inst].getPointee(A);
    return Pointee;
}
AliasMap PointsToAnalysis::getAliasOut(llvm::Instruction* Inst) {
    AliasMap Pointee;
    if (AliasOut.find(Inst) == AliasOut.end()) return Pointee;
    Pointee = AliasOut[Inst];
    return Pointee;
}
AliasUtil::Alias* PointsToAnalysis::getUniqueInstPointee(
    AliasUtil::Alias* A, llvm::Instruction* Inst) {
    AliasUtil::Alias* Result = nullptr;
    auto Pointee = AliasOut[Inst].getPointee(A);
    if (Pointee.size() == 1) {
        for (auto X : Pointee) {
            if (X->getName().endswith("-orig")) {
                Result = X;
            }
        }
    }
    return Result;
}
void PointsToAnalysis::printResults(llvm::Module& M) {
    int InstId = 0;
    for (Function& F : M.functions()) {
        for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
            std::cout << AliasIn[&*I] << std::endl;
            llvm::errs() << "[Instruction] " << InstId << " : " << *I << "\n\n";
            std::cout << AliasOut[&*I];
            std::cout << "----------- \n";
            InstId += 1;
        }
    }
    std::cout << Bench;
}
