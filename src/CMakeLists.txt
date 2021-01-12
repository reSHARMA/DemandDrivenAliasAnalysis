set(LLVM_LINK_COMPONENTS core support irreader passes)
add_executable(DDAADriver Driver.cpp)
set_target_properties(DDAADriver PROPERTIES
    COMPILE_FLAGS "-std=c++14 -fno-rtti"
)

llvm_config (DDAADriver ${LLVM_LINK_COMPONENTS})

target_link_libraries(DDAADriver PRIVATE AliasAnalysis)
