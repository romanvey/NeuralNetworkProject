# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /home/zabulskyy/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4203.549/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/zabulskyy/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/181.4203.549/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zabulskyy/Projects/Parallel-NN-C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NeuralNetwork.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NeuralNetwork.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NeuralNetwork.dir/flags.make

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o: CMakeFiles/NeuralNetwork.dir/flags.make
CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o: ../neural_network.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o -c /home/zabulskyy/Projects/Parallel-NN-C++/neural_network.cpp

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuralNetwork.dir/neural_network.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/Projects/Parallel-NN-C++/neural_network.cpp > CMakeFiles/NeuralNetwork.dir/neural_network.cpp.i

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuralNetwork.dir/neural_network.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/Projects/Parallel-NN-C++/neural_network.cpp -o CMakeFiles/NeuralNetwork.dir/neural_network.cpp.s

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.requires:

.PHONY : CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.requires

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.provides: CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuralNetwork.dir/build.make CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.provides.build
.PHONY : CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.provides

CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.provides.build: CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o


CMakeFiles/NeuralNetwork.dir/dense.cpp.o: CMakeFiles/NeuralNetwork.dir/flags.make
CMakeFiles/NeuralNetwork.dir/dense.cpp.o: ../dense.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/NeuralNetwork.dir/dense.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuralNetwork.dir/dense.cpp.o -c /home/zabulskyy/Projects/Parallel-NN-C++/dense.cpp

CMakeFiles/NeuralNetwork.dir/dense.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuralNetwork.dir/dense.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/Projects/Parallel-NN-C++/dense.cpp > CMakeFiles/NeuralNetwork.dir/dense.cpp.i

CMakeFiles/NeuralNetwork.dir/dense.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuralNetwork.dir/dense.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/Projects/Parallel-NN-C++/dense.cpp -o CMakeFiles/NeuralNetwork.dir/dense.cpp.s

CMakeFiles/NeuralNetwork.dir/dense.cpp.o.requires:

.PHONY : CMakeFiles/NeuralNetwork.dir/dense.cpp.o.requires

CMakeFiles/NeuralNetwork.dir/dense.cpp.o.provides: CMakeFiles/NeuralNetwork.dir/dense.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuralNetwork.dir/build.make CMakeFiles/NeuralNetwork.dir/dense.cpp.o.provides.build
.PHONY : CMakeFiles/NeuralNetwork.dir/dense.cpp.o.provides

CMakeFiles/NeuralNetwork.dir/dense.cpp.o.provides.build: CMakeFiles/NeuralNetwork.dir/dense.cpp.o


CMakeFiles/NeuralNetwork.dir/layer.cpp.o: CMakeFiles/NeuralNetwork.dir/flags.make
CMakeFiles/NeuralNetwork.dir/layer.cpp.o: ../layer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/NeuralNetwork.dir/layer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuralNetwork.dir/layer.cpp.o -c /home/zabulskyy/Projects/Parallel-NN-C++/layer.cpp

CMakeFiles/NeuralNetwork.dir/layer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuralNetwork.dir/layer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/Projects/Parallel-NN-C++/layer.cpp > CMakeFiles/NeuralNetwork.dir/layer.cpp.i

CMakeFiles/NeuralNetwork.dir/layer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuralNetwork.dir/layer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/Projects/Parallel-NN-C++/layer.cpp -o CMakeFiles/NeuralNetwork.dir/layer.cpp.s

CMakeFiles/NeuralNetwork.dir/layer.cpp.o.requires:

.PHONY : CMakeFiles/NeuralNetwork.dir/layer.cpp.o.requires

CMakeFiles/NeuralNetwork.dir/layer.cpp.o.provides: CMakeFiles/NeuralNetwork.dir/layer.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuralNetwork.dir/build.make CMakeFiles/NeuralNetwork.dir/layer.cpp.o.provides.build
.PHONY : CMakeFiles/NeuralNetwork.dir/layer.cpp.o.provides

CMakeFiles/NeuralNetwork.dir/layer.cpp.o.provides.build: CMakeFiles/NeuralNetwork.dir/layer.cpp.o


CMakeFiles/NeuralNetwork.dir/activation.cpp.o: CMakeFiles/NeuralNetwork.dir/flags.make
CMakeFiles/NeuralNetwork.dir/activation.cpp.o: ../activation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/NeuralNetwork.dir/activation.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/NeuralNetwork.dir/activation.cpp.o -c /home/zabulskyy/Projects/Parallel-NN-C++/activation.cpp

CMakeFiles/NeuralNetwork.dir/activation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NeuralNetwork.dir/activation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zabulskyy/Projects/Parallel-NN-C++/activation.cpp > CMakeFiles/NeuralNetwork.dir/activation.cpp.i

CMakeFiles/NeuralNetwork.dir/activation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NeuralNetwork.dir/activation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zabulskyy/Projects/Parallel-NN-C++/activation.cpp -o CMakeFiles/NeuralNetwork.dir/activation.cpp.s

CMakeFiles/NeuralNetwork.dir/activation.cpp.o.requires:

.PHONY : CMakeFiles/NeuralNetwork.dir/activation.cpp.o.requires

CMakeFiles/NeuralNetwork.dir/activation.cpp.o.provides: CMakeFiles/NeuralNetwork.dir/activation.cpp.o.requires
	$(MAKE) -f CMakeFiles/NeuralNetwork.dir/build.make CMakeFiles/NeuralNetwork.dir/activation.cpp.o.provides.build
.PHONY : CMakeFiles/NeuralNetwork.dir/activation.cpp.o.provides

CMakeFiles/NeuralNetwork.dir/activation.cpp.o.provides.build: CMakeFiles/NeuralNetwork.dir/activation.cpp.o


# Object files for target NeuralNetwork
NeuralNetwork_OBJECTS = \
"CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o" \
"CMakeFiles/NeuralNetwork.dir/dense.cpp.o" \
"CMakeFiles/NeuralNetwork.dir/layer.cpp.o" \
"CMakeFiles/NeuralNetwork.dir/activation.cpp.o"

# External object files for target NeuralNetwork
NeuralNetwork_EXTERNAL_OBJECTS =

NeuralNetwork: CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o
NeuralNetwork: CMakeFiles/NeuralNetwork.dir/dense.cpp.o
NeuralNetwork: CMakeFiles/NeuralNetwork.dir/layer.cpp.o
NeuralNetwork: CMakeFiles/NeuralNetwork.dir/activation.cpp.o
NeuralNetwork: CMakeFiles/NeuralNetwork.dir/build.make
NeuralNetwork: CMakeFiles/NeuralNetwork.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable NeuralNetwork"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NeuralNetwork.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NeuralNetwork.dir/build: NeuralNetwork

.PHONY : CMakeFiles/NeuralNetwork.dir/build

CMakeFiles/NeuralNetwork.dir/requires: CMakeFiles/NeuralNetwork.dir/neural_network.cpp.o.requires
CMakeFiles/NeuralNetwork.dir/requires: CMakeFiles/NeuralNetwork.dir/dense.cpp.o.requires
CMakeFiles/NeuralNetwork.dir/requires: CMakeFiles/NeuralNetwork.dir/layer.cpp.o.requires
CMakeFiles/NeuralNetwork.dir/requires: CMakeFiles/NeuralNetwork.dir/activation.cpp.o.requires

.PHONY : CMakeFiles/NeuralNetwork.dir/requires

CMakeFiles/NeuralNetwork.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NeuralNetwork.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NeuralNetwork.dir/clean

CMakeFiles/NeuralNetwork.dir/depend:
	cd /home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zabulskyy/Projects/Parallel-NN-C++ /home/zabulskyy/Projects/Parallel-NN-C++ /home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug /home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug /home/zabulskyy/Projects/Parallel-NN-C++/cmake-build-debug/CMakeFiles/NeuralNetwork.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NeuralNetwork.dir/depend

