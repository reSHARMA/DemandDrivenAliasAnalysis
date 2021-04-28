#include "DemandDrivenPointsToAnalysis.h"
#include "DemandDrivenPointsToAnalysisDriver.h"
#include "FlowSensitivePointsToAnalysis.h"
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

DemandDrivenPointsToAnalysis::DemandDrivenPointsToAnalysis(
    llvm::Instruction *Origin, llvm::Module &M) {
  TW = new spatial::TokenWrapper();
  IM = new spatial::GenericInstModel(TW);
  PointsToWorklist = new std::stack<llvm::Instruction *>();
  DemandWorklist = new std::stack<llvm::Instruction *>();
  PA = new FlowSensitiveAA::PointsToAnalysis(M, TW, IM, PointsToWorklist);
  DA = new SimpleDA::DemandAnalysis(TW, IM, DemandWorklist, Origin);
  PA->setDemandAnalysis(DA);
  DA->setPointsToAnalysis(PA);
  DemandWorklist->push(Origin);
}

void DemandDrivenPointsToAnalysis::run() {
  while (!(DemandWorklist->empty() && PointsToWorklist->empty())) {
    while (!DemandWorklist->empty()) {
      Instruction *Inst = DemandWorklist->top();
      DemandWorklist->pop();
      auto OldDemandInfo = DA->getDemandIn(Inst);
      DA->runAnalysis(Inst);
      auto NewDemandInfo = DA->getDemandIn(Inst);
      if (!(OldDemandInfo == NewDemandInfo)) {
        for (Instruction *I : spatial::GetPred(Inst)) {
          DemandWorklist->push(I);
          PointsToWorklist->push(I);
        }
      }
    }
    while (!PointsToWorklist->empty()) {
      Instruction *Inst = PointsToWorklist->top();
      PointsToWorklist->pop();
      PointsToGraph OldPointsToInfo = PA->getPointsToOut(Inst);
      PA->runAnalysis(Inst);
      PointsToGraph NewPointsToInfo = PA->getPointsToOut(Inst);
      if (!(OldPointsToInfo == NewPointsToInfo)) {
        for (Instruction *I : spatial::GetSucc(Inst)) {
          PointsToWorklist->push(I);
          DemandWorklist->push(I);
        }
      }
    }
  }
}
void DemandDrivenPointsToAnalysis::printDataFlowValues(llvm::Module &M) {
  DA->printResults(M);
  PA->printResults(M);
}
void DemandDrivenPointsToAnalysis::printResult(llvm::Instruction *Inst) {
  auto Temp = PA->getPointsToOut(Inst);
  PointsToGraph Result;
  for (auto X : Temp) {
    if (X.first->getName().endswith("-orig")) {
      Result.insert(X.first, X.second);
    }
  }
  std::cout << Result;
}
