# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build

# Include any dependencies generated for this target.
include lib/CMakeFiles/AliasAnalysis.dir/depend.make

# Include the progress variables for this target.
include lib/CMakeFiles/AliasAnalysis.dir/progress.make

# Include the compile flags for this target's objects.
include lib/CMakeFiles/AliasAnalysis.dir/flags.make

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o: lib/CMakeFiles/AliasAnalysis.dir/flags.make
lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o: ../lib/DemandDrivenAliasAnalysisDriver.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o -c /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysisDriver.cpp

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.i"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysisDriver.cpp > CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.i

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.s"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysisDriver.cpp -o CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.s

lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o: lib/CMakeFiles/AliasAnalysis.dir/flags.make
lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o: ../lib/FlowSensitiveAliasAnalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o -c /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/FlowSensitiveAliasAnalysis.cpp

lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.i"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/FlowSensitiveAliasAnalysis.cpp > CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.i

lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.s"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/FlowSensitiveAliasAnalysis.cpp -o CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.s

lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o: lib/CMakeFiles/AliasAnalysis.dir/flags.make
lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o: ../lib/SimpleDemandAnalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o -c /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/SimpleDemandAnalysis.cpp

lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.i"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/SimpleDemandAnalysis.cpp > CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.i

lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.s"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/SimpleDemandAnalysis.cpp -o CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.s

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o: lib/CMakeFiles/AliasAnalysis.dir/flags.make
lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o: ../lib/DemandDrivenAliasAnalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o -c /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysis.cpp

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.i"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysis.cpp > CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.i

lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.s"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib/DemandDrivenAliasAnalysis.cpp -o CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.s

# Object files for target AliasAnalysis
AliasAnalysis_OBJECTS = \
"CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o" \
"CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o" \
"CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o" \
"CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o"

# External object files for target AliasAnalysis
AliasAnalysis_EXTERNAL_OBJECTS =

lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysisDriver.cpp.o
lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/FlowSensitiveAliasAnalysis.cpp.o
lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/SimpleDemandAnalysis.cpp.o
lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/DemandDrivenAliasAnalysis.cpp.o
lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/build.make
lib/libAliasAnalysis.so: /usr/local/lib/libSpatial.so
lib/libAliasAnalysis.so: lib/CMakeFiles/AliasAnalysis.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libAliasAnalysis.so"
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AliasAnalysis.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/CMakeFiles/AliasAnalysis.dir/build: lib/libAliasAnalysis.so

.PHONY : lib/CMakeFiles/AliasAnalysis.dir/build

lib/CMakeFiles/AliasAnalysis.dir/clean:
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib && $(CMAKE_COMMAND) -P CMakeFiles/AliasAnalysis.dir/cmake_clean.cmake
.PHONY : lib/CMakeFiles/AliasAnalysis.dir/clean

lib/CMakeFiles/AliasAnalysis.dir/depend:
	cd /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/lib /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib /home/kaushik/Desktop/MTP/DemandDrivenAliasAnalysis/build/lib/CMakeFiles/AliasAnalysis.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/CMakeFiles/AliasAnalysis.dir/depend

