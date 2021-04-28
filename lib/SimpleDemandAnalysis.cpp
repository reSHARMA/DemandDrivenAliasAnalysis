#include "SimpleDemandAnalysis.h"
#include "DemandDrivenPointsToAnalysisDriver.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "set"
#include "spatial/Graph/Graph.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "spatial/Utils/CFGUtils.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"

using namespace llvm;
using namespace SimpleDA;
using PointsToGraph = spatial::Graph<spatial::Token>;

void DemandAnalysis::handleCallReturn(llvm::Instruction *Inst) {
  DemandIn[Inst] = DemandOut[Inst];
  if (CallInst *CI = dyn_cast<CallInst>(Inst)) {
    Function &Func = *CI->getCalledFunction();
    // handle return value
    if (!CI->doesNotReturn()) {
      if (ReturnInst *RI = dyn_cast<ReturnInst>(&(Func.back().back()))) {
        auto CallTokens = IM->extractToken(RI);
        if (CallTokens.size() == 1) {
          DemandOut[&(Func.back().back())].insert(CallTokens[0]);
        }
      }
    }
    // handle change made to globals
    for (auto P : DemandIn[&Func.front().front()]) {
      if (P->isGlobalVar()) {
        DemandIn[Inst].insert(P);
      }
    }
  }
}
void DemandAnalysis::runAnalysis(llvm::Instruction *Inst) {
  llvm::BasicBlock *ParentBB = Inst->getParent();
  llvm::Function *ParentFunc = ParentBB->getParent();
  std::vector<std::set<spatial::Token *>> Successors;
  // Extract alias tokens from the instruction
  auto Tokens = IM->extractToken(Inst);
  if (Inst == this->Origin && Tokens.size() > 0) {
    DemandOut[Inst].insert(Tokens[0]);
  }
  // Calculate control flow predecessor
  for (Instruction *I : spatial::GetSucc(Inst)) {
    if (DemandIn.find(I) != DemandIn.end())
      Successors.push_back(DemandIn[I]);
  }
  for (auto T : Successors) {
    DemandOut[Inst].insert(T.begin(), T.end());
  }
  DemandIn[Inst] = DemandOut[Inst];
  // handle function call
  if (CallInst *CI = dyn_cast<CallInst>(Inst)) {
    if (!CI->isIndirectCall()) {
      Function &Func = *CI->getCalledFunction();
      if (!spatial::SkipFunction(Func)) {
        // handle pass by reference
        for (Value *Arg : CI->args()) {
          spatial::Token *ActualArg = TW->getToken(new spatial::Token(Arg));
          DemandOut[&(Func.back().back())].insert(ActualArg);
          // If Actual argument points-to its dummy node then
          // also insert its source mapped pointee
          auto ActualArgPointee = AA->getUniqueInstPointee(ActualArg, Inst);
          if (ActualArgPointee)
            DemandOut[&(Func.back().back())].insert(ActualArgPointee);
        }
        this->CallGraph[&Func].insert(Inst);
        this->WorkList->push(&(Func.front().front()));
        this->handleCallReturn(Inst);
      }
    }
  }
  if (&ParentBB->front() == Inst) {
    for (auto C : this->CallGraph[ParentFunc]) {
      this->handleCallReturn(C);
    }
  }
  // Find the relative redirection between lhs and rhs
  // example for a = &b:(1, 0)
  auto Redirections = IM->extractRedirections(Inst);
  if (Tokens.size() == 2) {
    // Default behavior is copy ie (1, 1)
    // Handle *x = y
    if (Redirections[0] == 2) {
      DemandIn[Inst].insert(Tokens.begin(), Tokens.end());
      for (auto A : AA->getPointsToOut(Tokens[0], Inst)) {
        DemandIn[Inst].insert(A);
      }
    } else if (Redirections[1] == 2) {
      if (DemandOut[Inst].find(Tokens[0]) != DemandOut[Inst].end()) {
        DemandIn[Inst].insert(Tokens[1]);
        for (auto A : AA->getPointsToOut(Tokens[1], Inst)) {
          DemandIn[Inst].insert(A);
          for (auto Temp : AA->getPointsToOut(A, Inst)) {
            DemandIn[Inst].insert(Temp);
          }
        }
      }
    } else if (Redirections[1] == 1) {
      DemandIn[Inst].insert(Tokens[1]);
    }
  }
  // Handle killing
  if (Redirections[0] == 1) {
    if (Tokens.size() == 2) {
      if (DemandIn[Inst].find(Tokens[0]) != DemandIn[Inst].end())
        DemandIn[Inst].erase(Tokens[0]);
    }
  }
}
void DemandAnalysis::printResults(llvm::Module &M) {
  int InstId = 0;
  for (Function &F : M.functions()) {
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
      for (auto X : DemandIn[&*I])
        std::cout << *X << ", ";
      std::cout << std::endl;
      llvm::errs() << "\t [Instruction] " << InstId << " : " << *I << "\n";
      for (auto X : DemandOut[&*I])
        std::cout << *X << ", ";
      std::cout << "\n----------- \n";
      InstId += 1;
    }
  }
}
bool DemandAnalysis::inDemandOut(spatial::Token *Tok, llvm::Instruction *Inst) {
  bool Found = false;
  if (DemandOut.find(Inst) == DemandOut.end())
    return false;
  if (DemandOut[Inst].find(Tok) != DemandOut[Inst].end())
    Found = true;
  return Found;
}
std::set<spatial::Token *>
DemandAnalysis::getDemandOut(llvm::Instruction *Inst) {
  std::set<spatial::Token *> Demand;
  if (DemandOut.find(Inst) != DemandOut.end())
    Demand = DemandOut[Inst];
  return Demand;
}
std::set<spatial::Token *>
DemandAnalysis::getDemandIn(llvm::Instruction *Inst) {
  std::set<spatial::Token *> Demand;
  if (DemandIn.find(Inst) != DemandIn.end())
    Demand = DemandIn[Inst];
  return Demand;
}
