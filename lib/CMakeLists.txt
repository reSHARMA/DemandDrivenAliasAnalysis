add_library(AliasAnalysis SHARED
    DemandDrivenAliasAnalysisDriver.cpp
    FlowSensitiveAliasAnalysis.cpp
    SimpleDemandAnalysis.cpp
    DemandDrivenAliasAnalysis.cpp
)
set_target_properties(AliasAnalysis PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti"
)
target_link_libraries(AliasAnalysis AliasToken AliasBench CFGUtils)
