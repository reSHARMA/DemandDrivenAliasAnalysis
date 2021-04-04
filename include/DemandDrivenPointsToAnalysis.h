#ifndef DEMANDDRIVENPOINTSTOANALYSIS_H
#define DEMANDDRIVENPOINTSTOANALYSIS_H

#include "FlowSensitivePointsToAnalysis.h"
#include "SimpleDemandAnalysis.h"
#include "spatial/Token/TokenWrapper.h"
#include "stack"
#include "llvm/IR/Module.h"

using namespace llvm;

class DemandDrivenPointsToAnalysis {
private:
  spatial::TokenWrapper *TW;
  std::stack<llvm::Instruction *> *PointsToWorklist;
  std::stack<llvm::Instruction *> *DemandWorklist;
  FlowSensitiveAA::PointsToAnalysis *PA;
  SimpleDA::DemandAnalysis *DA;

public:
  DemandDrivenPointsToAnalysis(llvm::Instruction *Origin, llvm::Module &M);
  void run();
  void printDataFlowValues(llvm::Module &M);
  void printResult(llvm::Instruction *Inst);
};

#endif
