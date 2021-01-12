#ifndef SIMPLEDEMANDANALYSIS_H
#define SIMPLEDEMANDANALYSIS_H

#include "AliasBench/Benchmark.h"
#include "AliasGraph/AliasGraph.h"
#include "AliasToken/Alias.h"
#include "AliasToken/AliasToken.h"
#include "CFGUtils/CFGUtils.h"
#include "DemandDrivenAliasAnalysisDriver.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "map"
#include "set"
#include "stack"
#include "string"

using namespace llvm;
using AliasMap = AliasGraphUtil::AliasGraph<AliasUtil::Alias>;

namespace FlowSensitiveAA {
class PointsToAnalysis;
}

namespace SimpleDA {

class DemandAnalysis {
   private:
    std::map<Instruction*, std::set<AliasUtil::Alias*>> DemandIn, DemandOut;
    AliasUtil::AliasTokens* AT;
    std::stack<llvm::Instruction*>* WorkList;
    std::map<llvm::Function*, std::set<llvm::Instruction*>> CallGraph;
    llvm::Instruction* Origin;
    FlowSensitiveAA::PointsToAnalysis* AA;

   public:
    DemandAnalysis(AliasUtil::AliasTokens* AT,
                   std::stack<llvm::Instruction*>* W, llvm::Instruction* Origin)
        : AT(AT), WorkList(W), Origin(Origin), AA(nullptr) {
        WorkList->push(this->Origin);
    }
    void setAliasAnalysis(FlowSensitiveAA::PointsToAnalysis* AA) {
        this->AA = AA;
    }
    void handleCallReturn(llvm::Instruction* Inst);
    void runAnalysis(llvm::Instruction* Inst);
    void printResults(llvm::Module& M);
    bool inDemandOut(AliasUtil::Alias* Tok, llvm::Instruction* Inst);
    std::set<AliasUtil::Alias*> getDemandOut(llvm::Instruction* Inst);
    std::set<AliasUtil::Alias*> getDemandIn(llvm::Instruction* Inst);
};
}  // namespace SimpleDA

#endif
