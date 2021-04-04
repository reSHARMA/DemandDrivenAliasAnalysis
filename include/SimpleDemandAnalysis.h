#ifndef SIMPLEDEMANDANALYSIS_H
#define SIMPLEDEMANDANALYSIS_H

#include "DemandDrivenAliasAnalysisDriver.h"
#include "FlowSensitiveAliasAnalysis.h"
#include "iostream"
#include "map"
#include "set"
#include "spatial/Benchmark/Benchmark.h"
#include "spatial/Graph/Graph.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "stack"
#include "string"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"

using namespace llvm;
using PointsToGraph = spatial::Graph<spatial::Token>;

namespace FlowSensitiveAA {
class PointsToAnalysis;
}

namespace SimpleDA {

class DemandAnalysis {
private:
  std::map<Instruction *, std::set<spatial::Token *>> DemandIn, DemandOut;
  spatial::TokenWrapper *TW;
  std::stack<llvm::Instruction *> *WorkList;
  std::map<llvm::Function *, std::set<llvm::Instruction *>> CallGraph;
  llvm::Instruction *Origin;
  FlowSensitiveAA::PointsToAnalysis *AA;

public:
  DemandAnalysis(spatial::TokenWrapper *TW, std::stack<llvm::Instruction *> *W,
                 llvm::Instruction *Origin)
      : TW(TW), WorkList(W), Origin(Origin), AA(nullptr) {
    WorkList->push(this->Origin);
  }
  void setAliasAnalysis(FlowSensitiveAA::PointsToAnalysis *AA) {
    this->AA = AA;
  }
  void handleCallReturn(llvm::Instruction *Inst);
  void runAnalysis(llvm::Instruction *Inst);
  void printResults(llvm::Module &M);
  bool inDemandOut(spatial::Token *Tok, llvm::Instruction *Inst);
  std::set<spatial::Token *> getDemandOut(llvm::Instruction *Inst);
  std::set<spatial::Token *> getDemandIn(llvm::Instruction *Inst);
};
} // namespace SimpleDA

#endif
