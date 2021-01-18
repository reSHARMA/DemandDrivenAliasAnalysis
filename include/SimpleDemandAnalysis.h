#ifndef SIMPLEDEMANDANALYSIS_H
#define SIMPLEDEMANDANALYSIS_H

#include "DemandDrivenAliasAnalysisDriver.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "iostream"
#include "llvm/IR/InstIterator.h"
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

namespace FlowSensitiveAA {
class PointsToAnalysis;
}

namespace SimpleDA {

class DemandAnalysis {
   private:
    std::map<Instruction*, std::set<spatial::Alias*>> DemandIn, DemandOut;
    spatial::AliasTokens* AT;
    std::stack<llvm::Instruction*>* WorkList;
    std::map<llvm::Function*, std::set<llvm::Instruction*>> CallGraph;
    llvm::Instruction* Origin;
    FlowSensitiveAA::PointsToAnalysis* AA;

   public:
    DemandAnalysis(spatial::AliasTokens* AT, std::stack<llvm::Instruction*>* W,
                   llvm::Instruction* Origin)
        : AT(AT), WorkList(W), Origin(Origin), AA(nullptr) {
        WorkList->push(this->Origin);
    }
    void setAliasAnalysis(FlowSensitiveAA::PointsToAnalysis* AA) {
        this->AA = AA;
    }
    void handleCallReturn(llvm::Instruction* Inst);
    void runAnalysis(llvm::Instruction* Inst);
    void printResults(llvm::Module& M);
    bool inDemandOut(spatial::Alias* Tok, llvm::Instruction* Inst);
    std::set<spatial::Alias*> getDemandOut(llvm::Instruction* Inst);
    std::set<spatial::Alias*> getDemandIn(llvm::Instruction* Inst);
};
}  // namespace SimpleDA

#endif
