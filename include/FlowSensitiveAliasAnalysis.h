#ifndef FLOWSENSITIVEALIASANALYSIS_H
#define FLOWSENSITIVEALIASANALYSIS_H

#include "AliasBench/Benchmark.h"
#include "AliasGraph/AliasGraph.h"
#include "AliasToken/Alias.h"
#include "AliasToken/AliasToken.h"
#include "CFGUtils/CFGUtils.h"
#include "DemandDrivenAliasAnalysisDriver.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "map"
#include "set"
#include "stack"
#include "string"

using namespace llvm;
using AliasMap = AliasGraphUtil::AliasGraph<AliasUtil::Alias>;

namespace SimpleDA {
class DemandAnalysis;
}

namespace FlowSensitiveAA {

class PointsToAnalysis {
   private:
    AliasMap GlobalAliasMap;
    std::map<Instruction*, AliasMap> AliasIn, AliasOut;
    AliasUtil::AliasTokens* AT;
    BenchmarkUtil::BenchmarkRunner Bench;
    std::stack<llvm::Instruction*>* WorkList;
    std::map<llvm::Function*, std::set<llvm::Instruction*>> CallGraph;
    SimpleDA::DemandAnalysis* DA;

   public:
    PointsToAnalysis(Module& M, AliasUtil::AliasTokens* AT,
                     std::stack<llvm::Instruction*>* W)
        : AT(AT), WorkList(W), DA(nullptr) {
        initializeWorkList(M);
        handleGlobalVar(M);
    }
    void setDemandAnalysis(SimpleDA::DemandAnalysis* DA) { this->DA = DA; }
    void handleGlobalVar(llvm::Module& M);
    void handleCallReturn(llvm::Instruction* Inst);
    void initializeWorkList(llvm::Module& M);
    bool isInDemandOut(AliasUtil::Alias* A, llvm::Instruction* Inst);
    void runAnalysis(llvm::Instruction* Inst);
    std::set<AliasUtil::Alias*> getAliasOut(AliasUtil::Alias* A,
                                            llvm::Instruction* Inst);
    AliasMap getAliasOut(llvm::Instruction* Inst);
    AliasUtil::Alias* getUniqueInstPointee(AliasUtil::Alias* A,
                                           llvm::Instruction* Inst);
    void printResults(llvm::Module& M);
};
}  // namespace FlowSensitiveAA

#endif
