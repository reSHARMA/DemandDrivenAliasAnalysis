add_library(PointsToAnalysis SHARED
    DemandDrivenPointsToAnalysisDriver.cpp
    FlowSensitivePointsToAnalysis.cpp
    SimpleDemandAnalysis.cpp
    DemandDrivenPointsToAnalysis.cpp
)
set_target_properties(PointsToAnalysis PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti"
)
target_link_libraries(PointsToAnalysis Spatial)
