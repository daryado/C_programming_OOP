# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.15

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Clabs\Upper_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Clabs\Upper_project\cmake-build-debug

# Include any dependencies generated for this target.
include gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/depend.make

# Include the progress variables for this target.
include gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/progress.make

# Include the compile flags for this target's objects.
include gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/flags.make

gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj: gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/flags.make
gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj: gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/includes_CXX.rsp
gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj: ../gtestset/lib/googletest-master/googlemock/src/gmock-all.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Clabs\Upper_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj"
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\gmock.dir\src\gmock-all.cc.obj -c D:\Clabs\Upper_project\gtestset\lib\googletest-master\googlemock\src\gmock-all.cc

gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gmock.dir/src/gmock-all.cc.i"
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Clabs\Upper_project\gtestset\lib\googletest-master\googlemock\src\gmock-all.cc > CMakeFiles\gmock.dir\src\gmock-all.cc.i

gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gmock.dir/src/gmock-all.cc.s"
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Clabs\Upper_project\gtestset\lib\googletest-master\googlemock\src\gmock-all.cc -o CMakeFiles\gmock.dir\src\gmock-all.cc.s

# Object files for target gmock
gmock_OBJECTS = \
"CMakeFiles/gmock.dir/src/gmock-all.cc.obj"

# External object files for target gmock
gmock_EXTERNAL_OBJECTS =

lib/libgmockd.a: gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.obj
lib/libgmockd.a: gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/build.make
lib/libgmockd.a: gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Clabs\Upper_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ..\..\..\..\lib\libgmockd.a"
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && $(CMAKE_COMMAND) -P CMakeFiles\gmock.dir\cmake_clean_target.cmake
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\gmock.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/build: lib/libgmockd.a

.PHONY : gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/build

gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/clean:
	cd /d D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock && $(CMAKE_COMMAND) -P CMakeFiles\gmock.dir\cmake_clean.cmake
.PHONY : gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/clean

gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Clabs\Upper_project D:\Clabs\Upper_project\gtestset\lib\googletest-master\googlemock D:\Clabs\Upper_project\cmake-build-debug D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock D:\Clabs\Upper_project\cmake-build-debug\gtestset\lib\googletest-master\googlemock\CMakeFiles\gmock.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : gtestset/lib/googletest-master/googlemock/CMakeFiles/gmock.dir/depend

