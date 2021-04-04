#include "DemandDrivenPointsToAnalysisDriver.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/Utils/UnifyFunctionExitNodes.h"

using namespace llvm;

int main(int argc, char** argv) {
    if (argc < 1) return 1;
    LLVMContext Context;
    SMDiagnostic Error;
    std::unique_ptr<Module> M = parseIRFile(argv[1], Error, Context);
    legacy::FunctionPassManager FPM(M.get());
    Pass* UEN = createUnifyFunctionExitNodesPass();
    FPM.add(UEN);
    for (Function& F : M.get()->functions()) {
        FPM.run(F);
    }
    // TODO Parse cli args elegantly
    if (argc == 2) {
        DemandDrivenPointsToAnalysisDriverPass* AAP =
            new DemandDrivenPointsToAnalysisDriverPass();
        AAP->runOnModule(*M);
    }
    return 0;
}
