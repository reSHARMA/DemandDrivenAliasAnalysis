#ifndef FLOWSENSITIVEPOINTSTOANALYSIS_H
#define FLOWSENSITIVEPOINTSTOANALYSIS_H

#include "DemandDrivenPointsToAnalysisDriver.h"
#include "SimpleDemandAnalysis.h"
#include "iostream"
#include "map"
#include "set"
#include "spatial/Benchmark/PTABenchmark.h"
#include "spatial/Graph/Graph.h"
#include "spatial/Token/Token.h"
#include "spatial/Token/TokenWrapper.h"
#include "stack"
#include "string"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"

using namespace llvm;
using PointsToGraph = spatial::Graph<spatial::Token>;

namespace SimpleDA {
class DemandAnalysis;
}

namespace FlowSensitiveAA {

class PointsToAnalysis {
private:
  PointsToGraph GlobalPointsToGraph;
  std::map<Instruction *, PointsToGraph> PointsToIn, PointsToOut;
  spatial::TokenWrapper *TW;
  spatial::PTABenchmarkRunner Bench;
  std::stack<llvm::Instruction *> *WorkList;
  std::map<llvm::Function *, std::set<llvm::Instruction *>> CallGraph;
  SimpleDA::DemandAnalysis *DA;

public:
  PointsToAnalysis(Module &M, spatial::TokenWrapper *TW,
                   std::stack<llvm::Instruction *> *W)
      : TW(TW), WorkList(W), DA(nullptr) {
    initializeWorkList(M);
    handleGlobalVar(M);
  }
  void setDemandAnalysis(SimpleDA::DemandAnalysis *DA) { this->DA = DA; }
  void handleGlobalVar(llvm::Module &M);
  void handleCallReturn(llvm::Instruction *Inst);
  void initializeWorkList(llvm::Module &M);
  bool isInDemandOut(spatial::Token *A, llvm::Instruction *Inst);
  void runAnalysis(llvm::Instruction *Inst);
  std::set<spatial::Token *> getPointsToOut(spatial::Token *A,
                                         llvm::Instruction *Inst);
  PointsToGraph getPointsToOut(llvm::Instruction *Inst);
  spatial::Token *getUniqueInstPointee(spatial::Token *A,
                                       llvm::Instruction *Inst);
  void printResults(llvm::Module &M);
};
} // namespace FlowSensitiveAA

#endif
