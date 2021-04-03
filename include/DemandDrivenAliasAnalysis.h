#ifndef DEMANDDRIVENALIASANALYSIS_H
#define DEMANDDRIVENALIASANALYSIS_H

#include "FlowSensitiveAliasAnalysis.h"
#include "SimpleDemandAnalysis.h"
#include "spatial/Token/TokenWrapper.h"
#include "stack"
#include "llvm/IR/Module.h"

using namespace llvm;

class DemandDrivenAliasAnalysis {
private:
  spatial::TokenWrapper *TW;
  std::stack<llvm::Instruction *> *AliasWorklist;
  std::stack<llvm::Instruction *> *DemandWorklist;
  FlowSensitiveAA::PointsToAnalysis *PA;
  SimpleDA::DemandAnalysis *DA;

public:
  DemandDrivenAliasAnalysis(llvm::Instruction *Origin, llvm::Module &M);
  void run();
  void printDataFlowValues(llvm::Module &M);
  void printResult(llvm::Instruction *Inst);
};

#endif
