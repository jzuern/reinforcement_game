# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /home/jannik/clion-2017.3.1/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jannik/clion-2017.3.1/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jannik/Desktop/project_0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jannik/Desktop/project_0/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project0.dir/flags.make

CMakeFiles/project0.dir/src/main.cpp.o: CMakeFiles/project0.dir/flags.make
CMakeFiles/project0.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project0.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project0.dir/src/main.cpp.o -c /home/jannik/Desktop/project_0/src/main.cpp

CMakeFiles/project0.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project0.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jannik/Desktop/project_0/src/main.cpp > CMakeFiles/project0.dir/src/main.cpp.i

CMakeFiles/project0.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project0.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jannik/Desktop/project_0/src/main.cpp -o CMakeFiles/project0.dir/src/main.cpp.s

CMakeFiles/project0.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/project0.dir/src/main.cpp.o.requires

CMakeFiles/project0.dir/src/main.cpp.o.provides: CMakeFiles/project0.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/project0.dir/build.make CMakeFiles/project0.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/project0.dir/src/main.cpp.o.provides

CMakeFiles/project0.dir/src/main.cpp.o.provides.build: CMakeFiles/project0.dir/src/main.cpp.o


CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o: CMakeFiles/project0.dir/flags.make
CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o: ../src/SimulatedDisk.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o -c /home/jannik/Desktop/project_0/src/SimulatedDisk.cpp

CMakeFiles/project0.dir/src/SimulatedDisk.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project0.dir/src/SimulatedDisk.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jannik/Desktop/project_0/src/SimulatedDisk.cpp > CMakeFiles/project0.dir/src/SimulatedDisk.cpp.i

CMakeFiles/project0.dir/src/SimulatedDisk.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project0.dir/src/SimulatedDisk.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jannik/Desktop/project_0/src/SimulatedDisk.cpp -o CMakeFiles/project0.dir/src/SimulatedDisk.cpp.s

CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.requires:

.PHONY : CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.requires

CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.provides: CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.requires
	$(MAKE) -f CMakeFiles/project0.dir/build.make CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.provides.build
.PHONY : CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.provides

CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.provides.build: CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o


CMakeFiles/project0.dir/src/Controller.cpp.o: CMakeFiles/project0.dir/flags.make
CMakeFiles/project0.dir/src/Controller.cpp.o: ../src/Controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project0.dir/src/Controller.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project0.dir/src/Controller.cpp.o -c /home/jannik/Desktop/project_0/src/Controller.cpp

CMakeFiles/project0.dir/src/Controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project0.dir/src/Controller.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jannik/Desktop/project_0/src/Controller.cpp > CMakeFiles/project0.dir/src/Controller.cpp.i

CMakeFiles/project0.dir/src/Controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project0.dir/src/Controller.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jannik/Desktop/project_0/src/Controller.cpp -o CMakeFiles/project0.dir/src/Controller.cpp.s

CMakeFiles/project0.dir/src/Controller.cpp.o.requires:

.PHONY : CMakeFiles/project0.dir/src/Controller.cpp.o.requires

CMakeFiles/project0.dir/src/Controller.cpp.o.provides: CMakeFiles/project0.dir/src/Controller.cpp.o.requires
	$(MAKE) -f CMakeFiles/project0.dir/build.make CMakeFiles/project0.dir/src/Controller.cpp.o.provides.build
.PHONY : CMakeFiles/project0.dir/src/Controller.cpp.o.provides

CMakeFiles/project0.dir/src/Controller.cpp.o.provides.build: CMakeFiles/project0.dir/src/Controller.cpp.o


CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o: CMakeFiles/project0.dir/flags.make
CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o: ../src/PolicyNetwork.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o -c /home/jannik/Desktop/project_0/src/PolicyNetwork.cpp

CMakeFiles/project0.dir/src/PolicyNetwork.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project0.dir/src/PolicyNetwork.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jannik/Desktop/project_0/src/PolicyNetwork.cpp > CMakeFiles/project0.dir/src/PolicyNetwork.cpp.i

CMakeFiles/project0.dir/src/PolicyNetwork.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project0.dir/src/PolicyNetwork.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jannik/Desktop/project_0/src/PolicyNetwork.cpp -o CMakeFiles/project0.dir/src/PolicyNetwork.cpp.s

CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.requires:

.PHONY : CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.requires

CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.provides: CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.requires
	$(MAKE) -f CMakeFiles/project0.dir/build.make CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.provides.build
.PHONY : CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.provides

CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.provides.build: CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o


# Object files for target project0
project0_OBJECTS = \
"CMakeFiles/project0.dir/src/main.cpp.o" \
"CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o" \
"CMakeFiles/project0.dir/src/Controller.cpp.o" \
"CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o"

# External object files for target project0
project0_EXTERNAL_OBJECTS =

project0: CMakeFiles/project0.dir/src/main.cpp.o
project0: CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o
project0: CMakeFiles/project0.dir/src/Controller.cpp.o
project0: CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o
project0: CMakeFiles/project0.dir/build.make
project0: /usr/lib/x86_64-linux-gnu/libsfml-network.so
project0: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
project0: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
project0: /usr/lib/x86_64-linux-gnu/libsfml-window.so
project0: /usr/lib/x86_64-linux-gnu/libsfml-system.so
project0: CMakeFiles/project0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable project0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project0.dir/build: project0

.PHONY : CMakeFiles/project0.dir/build

CMakeFiles/project0.dir/requires: CMakeFiles/project0.dir/src/main.cpp.o.requires
CMakeFiles/project0.dir/requires: CMakeFiles/project0.dir/src/SimulatedDisk.cpp.o.requires
CMakeFiles/project0.dir/requires: CMakeFiles/project0.dir/src/Controller.cpp.o.requires
CMakeFiles/project0.dir/requires: CMakeFiles/project0.dir/src/PolicyNetwork.cpp.o.requires

.PHONY : CMakeFiles/project0.dir/requires

CMakeFiles/project0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project0.dir/clean

CMakeFiles/project0.dir/depend:
	cd /home/jannik/Desktop/project_0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jannik/Desktop/project_0 /home/jannik/Desktop/project_0 /home/jannik/Desktop/project_0/cmake-build-debug /home/jannik/Desktop/project_0/cmake-build-debug /home/jannik/Desktop/project_0/cmake-build-debug/CMakeFiles/project0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project0.dir/depend

