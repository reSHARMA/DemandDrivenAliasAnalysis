set(LLVM_LINK_COMPONENTS core support irreader passes transformutils)
add_executable(DDPTDriver Driver.cpp)
set_target_properties(DDPTDriver PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti"
)

llvm_config (DDPTDriver ${LLVM_LINK_COMPONENTS})

target_link_libraries(DDPTDriver PRIVATE PointsToAnalysis)
