#ifndef DEMANDDRIVENALIASANALYSISDRIVER_H
#define DEMANDDRIVENALIASANALYSISDRIVER_H

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

class DemandDrivenAliasAnalysisDriverPass : public llvm::ModulePass {
   public:
    static char ID;
    DemandDrivenAliasAnalysisDriverPass() : ModulePass(ID) {}

    bool runOnModule(llvm::Module& M) override;
};

#endif
