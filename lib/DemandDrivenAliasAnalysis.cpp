#include "DemandDrivenAliasAnalysis.h"
#include "DemandDrivenAliasAnalysisDriver.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "spatial/Graph/Graph.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "spatial/Utils/CFGUtils.h"
#include "stack"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"

using namespace llvm;
using PointsToGraph = spatial::Graph<spatial::Token>;

DemandDrivenAliasAnalysis::DemandDrivenAliasAnalysis(llvm::Instruction *Origin,
                                                     llvm::Module &M) {
  TW = new spatial::TokenWrapper();
  AliasWorklist = new std::stack<llvm::Instruction *>();
  DemandWorklist = new std::stack<llvm::Instruction *>();
  PA = new FlowSensitiveAA::PointsToAnalysis(M, TW, AliasWorklist);
  DA = new SimpleDA::DemandAnalysis(TW, DemandWorklist, Origin);
  PA->setDemandAnalysis(DA);
  DA->setAliasAnalysis(PA);
  DemandWorklist->push(Origin);
}

void DemandDrivenAliasAnalysis::run() {
  while (!(DemandWorklist->empty() && AliasWorklist->empty())) {
    while (!DemandWorklist->empty()) {
      Instruction *Inst = DemandWorklist->top();
      DemandWorklist->pop();
      auto OldDemandInfo = DA->getDemandIn(Inst);
      DA->runAnalysis(Inst);
      auto NewDemandInfo = DA->getDemandIn(Inst);
      if (!(OldDemandInfo == NewDemandInfo)) {
        for (Instruction *I : spatial::GetPred(Inst)) {
          DemandWorklist->push(I);
          AliasWorklist->push(I);
        }
      }
    }
    while (!AliasWorklist->empty()) {
      Instruction *Inst = AliasWorklist->top();
      AliasWorklist->pop();
      PointsToGraph OldAliasInfo = PA->getAliasOut(Inst);
      PA->runAnalysis(Inst);
      PointsToGraph NewAliasInfo = PA->getAliasOut(Inst);
      if (!(OldAliasInfo == NewAliasInfo)) {
        for (Instruction *I : spatial::GetSucc(Inst)) {
          AliasWorklist->push(I);
          DemandWorklist->push(I);
        }
      }
    }
  }
}
void DemandDrivenAliasAnalysis::printDataFlowValues(llvm::Module &M) {
  DA->printResults(M);
  PA->printResults(M);
}
void DemandDrivenAliasAnalysis::printResult(llvm::Instruction *Inst) {
  auto Temp = PA->getAliasOut(Inst);
  PointsToGraph Result;
  for (auto X : Temp) {
    if (X.first->getName().endswith("-orig")) {
      Result.insert(X.first, X.second);
    }
  }
  std::cout << Result;
}
