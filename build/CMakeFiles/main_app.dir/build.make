# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mac/my-own/grace-api/tcp-producer-send-file-aws

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build

# Include any dependencies generated for this target.
include CMakeFiles/main_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main_app.dir/flags.make

CMakeFiles/main_app.dir/codegen:
.PHONY : CMakeFiles/main_app.dir/codegen

CMakeFiles/main_app.dir/app/main.cpp.o: CMakeFiles/main_app.dir/flags.make
CMakeFiles/main_app.dir/app/main.cpp.o: /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/app/main.cpp
CMakeFiles/main_app.dir/app/main.cpp.o: CMakeFiles/main_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main_app.dir/app/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main_app.dir/app/main.cpp.o -MF CMakeFiles/main_app.dir/app/main.cpp.o.d -o CMakeFiles/main_app.dir/app/main.cpp.o -c /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/app/main.cpp

CMakeFiles/main_app.dir/app/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main_app.dir/app/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/app/main.cpp > CMakeFiles/main_app.dir/app/main.cpp.i

CMakeFiles/main_app.dir/app/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main_app.dir/app/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/app/main.cpp -o CMakeFiles/main_app.dir/app/main.cpp.s

# Object files for target main_app
main_app_OBJECTS = \
"CMakeFiles/main_app.dir/app/main.cpp.o"

# External object files for target main_app
main_app_EXTERNAL_OBJECTS =

main_app: CMakeFiles/main_app.dir/app/main.cpp.o
main_app: CMakeFiles/main_app.dir/build.make
main_app: libstreamProducer.a
main_app: libtcpProducer.a
main_app: CMakeFiles/main_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable main_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/main_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main_app.dir/build: main_app
.PHONY : CMakeFiles/main_app.dir/build

CMakeFiles/main_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/main_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/main_app.dir/clean

CMakeFiles/main_app.dir/depend:
	cd /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mac/my-own/grace-api/tcp-producer-send-file-aws /Users/mac/my-own/grace-api/tcp-producer-send-file-aws /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build /Users/mac/my-own/grace-api/tcp-producer-send-file-aws/build/CMakeFiles/main_app.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main_app.dir/depend

