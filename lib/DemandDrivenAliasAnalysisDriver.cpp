#include "DemandDrivenAliasAnalysisDriver.h"
#include "DemandDrivenAliasAnalysis.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "spatial/Benchmark/Benchmark.h"
#include "spatial/Graph/Graph.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "spatial/Utils/CFGUtils.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"

using namespace llvm;

bool DemandDrivenAliasAnalysisDriverPass::runOnModule(Module &M) {
  std::vector<Instruction *> VirtualCallSites;
  for (Function &F : M.functions()) {
    spatial::InstNamer(F);
    for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I) {
      if (CallInst *CI = dyn_cast<CallInst>(&*I)) {
        if (CI->isIndirectCall() && CI->arg_size() == 1) {
          auto Virt = CI->getArgOperand(0);
          if (Instruction *Inst = dyn_cast<Instruction>(Virt)) {
            VirtualCallSites.push_back(Inst);
          }
        }
      }
    }
  }
  if (VirtualCallSites.empty()) {
    std::cout << "No virtual call site found! Aborting ...\n";
    return false;
  }
  for (Instruction *Inst : VirtualCallSites) {
    DemandDrivenAliasAnalysis DDAA(Inst, M);
    DDAA.run();
    DDAA.printDataFlowValues(M);
    DDAA.printResult(Inst);
  }
  return false;
}

char DemandDrivenAliasAnalysisDriverPass::ID = 0;
static RegisterPass<DemandDrivenAliasAnalysisDriverPass>
    X("sddaa", "Simple demand driven alias analysis in LLVM", true, true);
