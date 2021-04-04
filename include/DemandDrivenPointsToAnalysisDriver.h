#ifndef DEMANDDRIVENPOINTSTOANALYSISDRIVER_H
#define DEMANDDRIVENPOINTSTOANALYSISDRIVER_H

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

class DemandDrivenPointsToAnalysisDriverPass : public llvm::ModulePass {
public:
  static char ID;
  DemandDrivenPointsToAnalysisDriverPass() : ModulePass(ID) {}

  bool runOnModule(llvm::Module &M) override;
};

#endif
