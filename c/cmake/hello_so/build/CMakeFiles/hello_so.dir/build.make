# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/code/doing/cmake/hello_so

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/code/doing/cmake/hello_so/build

# Include any dependencies generated for this target.
include CMakeFiles/hello_so.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hello_so.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hello_so.dir/flags.make

CMakeFiles/hello_so.dir/main.c.o: CMakeFiles/hello_so.dir/flags.make
CMakeFiles/hello_so.dir/main.c.o: ../main.c
	$(CMAKE_COMMAND) -E cmake_progress_report /home/code/doing/cmake/hello_so/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/hello_so.dir/main.c.o"
	/home/gcc/4.4.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/hello_so.dir/main.c.o   -c /home/code/doing/cmake/hello_so/main.c

CMakeFiles/hello_so.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/hello_so.dir/main.c.i"
	/home/gcc/4.4.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -E /home/code/doing/cmake/hello_so/main.c > CMakeFiles/hello_so.dir/main.c.i

CMakeFiles/hello_so.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/hello_so.dir/main.c.s"
	/home/gcc/4.4.3/bin/arm-linux-gcc  $(C_DEFINES) $(C_FLAGS) -S /home/code/doing/cmake/hello_so/main.c -o CMakeFiles/hello_so.dir/main.c.s

CMakeFiles/hello_so.dir/main.c.o.requires:
.PHONY : CMakeFiles/hello_so.dir/main.c.o.requires

CMakeFiles/hello_so.dir/main.c.o.provides: CMakeFiles/hello_so.dir/main.c.o.requires
	$(MAKE) -f CMakeFiles/hello_so.dir/build.make CMakeFiles/hello_so.dir/main.c.o.provides.build
.PHONY : CMakeFiles/hello_so.dir/main.c.o.provides

CMakeFiles/hello_so.dir/main.c.o.provides.build: CMakeFiles/hello_so.dir/main.c.o
.PHONY : CMakeFiles/hello_so.dir/main.c.o.provides.build

# Object files for target hello_so
hello_so_OBJECTS = \
"CMakeFiles/hello_so.dir/main.c.o"

# External object files for target hello_so
hello_so_EXTERNAL_OBJECTS =

../hello_so: CMakeFiles/hello_so.dir/main.c.o
../hello_so: ../cstring/libztstring.so
../hello_so: CMakeFiles/hello_so.dir/build.make
../hello_so: CMakeFiles/hello_so.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable ../hello_so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hello_so.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hello_so.dir/build: ../hello_so
.PHONY : CMakeFiles/hello_so.dir/build

CMakeFiles/hello_so.dir/requires: CMakeFiles/hello_so.dir/main.c.o.requires
.PHONY : CMakeFiles/hello_so.dir/requires

CMakeFiles/hello_so.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hello_so.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hello_so.dir/clean

CMakeFiles/hello_so.dir/depend:
	cd /home/code/doing/cmake/hello_so/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/code/doing/cmake/hello_so /home/code/doing/cmake/hello_so /home/code/doing/cmake/hello_so/build /home/code/doing/cmake/hello_so/build /home/code/doing/cmake/hello_so/build/CMakeFiles/hello_so.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hello_so.dir/depend
