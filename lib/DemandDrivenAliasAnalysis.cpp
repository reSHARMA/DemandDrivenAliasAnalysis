#include "DemandDrivenAliasAnalysis.h"
#include "DemandDrivenAliasAnalysisDriver.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "spatial/Graph/AliasGraph.h"
#include "spatial/Token/Alias.h"
#include "spatial/Token/AliasToken.h"
#include "spatial/Utils/CFGUtils.h"
#include "stack"

using namespace llvm;
using AliasMap = spatial::AliasGraph<spatial::Alias>;

DemandDrivenAliasAnalysis::DemandDrivenAliasAnalysis(llvm::Instruction* Origin,
                                                     llvm::Module& M) {
    AT = new spatial::AliasTokens();
    AliasWorklist = new std::stack<llvm::Instruction*>();
    DemandWorklist = new std::stack<llvm::Instruction*>();
    PA = new FlowSensitiveAA::PointsToAnalysis(M, AT, AliasWorklist);
    DA = new SimpleDA::DemandAnalysis(AT, DemandWorklist, Origin);
    PA->setDemandAnalysis(DA);
    DA->setAliasAnalysis(PA);
    DemandWorklist->push(Origin);
}

void DemandDrivenAliasAnalysis::run() {
    while (!(DemandWorklist->empty() && AliasWorklist->empty())) {
        while (!DemandWorklist->empty()) {
            Instruction* Inst = DemandWorklist->top();
            DemandWorklist->pop();
            auto OldDemandInfo = DA->getDemandIn(Inst);
            DA->runAnalysis(Inst);
            auto NewDemandInfo = DA->getDemandIn(Inst);
            if (!(OldDemandInfo == NewDemandInfo)) {
                for (Instruction* I : spatial::GetPred(Inst)) {
                    DemandWorklist->push(I);
                    AliasWorklist->push(I);
                }
            }
        }
        while (!AliasWorklist->empty()) {
            Instruction* Inst = AliasWorklist->top();
            AliasWorklist->pop();
            AliasMap OldAliasInfo = PA->getAliasOut(Inst);
            PA->runAnalysis(Inst);
            AliasMap NewAliasInfo = PA->getAliasOut(Inst);
            if (!(OldAliasInfo == NewAliasInfo)) {
                for (Instruction* I : spatial::GetSucc(Inst)) {
                    AliasWorklist->push(I);
                    DemandWorklist->push(I);
                }
            }
        }
    }
}
void DemandDrivenAliasAnalysis::printDataFlowValues(llvm::Module& M) {
    DA->printResults(M);
    PA->printResults(M);
}
void DemandDrivenAliasAnalysis::printResult(llvm::Instruction* Inst) {
    auto Temp = PA->getAliasOut(Inst);
    AliasMap Result;
    for (auto X : Temp) {
        if (X.first->getName().endswith("-orig")) {
            Result.insert(X.first, X.second);
        }
    }
    std::cout << Result;
}
