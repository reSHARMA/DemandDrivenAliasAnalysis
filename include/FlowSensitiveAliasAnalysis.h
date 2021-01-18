#ifndef FLOWSENSITIVEALIASANALYSIS_H
#define FLOWSENSITIVEALIASANALYSIS_H

#include "DemandDrivenAliasAnalysisDriver.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "map"
#include "set"
#include "spatial/Benchmark/Benchmark.h"
#include "spatial/Graph/AliasGraph.h"
#include "spatial/Token/Alias.h"
#include "spatial/Token/AliasToken.h"
#include "stack"
#include "string"

using namespace llvm;
using AliasMap = spatial::AliasGraph<spatial::Alias>;

namespace SimpleDA {
class DemandAnalysis;
}

namespace FlowSensitiveAA {

class PointsToAnalysis {
   private:
    AliasMap GlobalAliasMap;
    std::map<Instruction*, AliasMap> AliasIn, AliasOut;
    spatial::AliasTokens* AT;
    spatial::BenchmarkRunner Bench;
    std::stack<llvm::Instruction*>* WorkList;
    std::map<llvm::Function*, std::set<llvm::Instruction*>> CallGraph;
    SimpleDA::DemandAnalysis* DA;

   public:
    PointsToAnalysis(Module& M, spatial::AliasTokens* AT,
                     std::stack<llvm::Instruction*>* W)
        : AT(AT), WorkList(W), DA(nullptr) {
        initializeWorkList(M);
        handleGlobalVar(M);
    }
    void setDemandAnalysis(SimpleDA::DemandAnalysis* DA) { this->DA = DA; }
    void handleGlobalVar(llvm::Module& M);
    void handleCallReturn(llvm::Instruction* Inst);
    void initializeWorkList(llvm::Module& M);
    bool isInDemandOut(spatial::Alias* A, llvm::Instruction* Inst);
    void runAnalysis(llvm::Instruction* Inst);
    std::set<spatial::Alias*> getAliasOut(spatial::Alias* A,
                                          llvm::Instruction* Inst);
    AliasMap getAliasOut(llvm::Instruction* Inst);
    spatial::Alias* getUniqueInstPointee(spatial::Alias* A,
                                         llvm::Instruction* Inst);
    void printResults(llvm::Module& M);
};
}  // namespace FlowSensitiveAA

#endif
