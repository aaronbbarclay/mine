# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aaronb/Dev/mine/theNextWeek

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aaronb/Dev/mine/theNextWeek/cmake-build

# Include any dependencies generated for this target.
include CMakeFiles/theNextWeek.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/theNextWeek.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/theNextWeek.dir/flags.make

CMakeFiles/theNextWeek.dir/src/main.cc.o: CMakeFiles/theNextWeek.dir/flags.make
CMakeFiles/theNextWeek.dir/src/main.cc.o: ../src/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aaronb/Dev/mine/theNextWeek/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/theNextWeek.dir/src/main.cc.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/theNextWeek.dir/src/main.cc.o -c /Users/aaronb/Dev/mine/theNextWeek/src/main.cc

CMakeFiles/theNextWeek.dir/src/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/theNextWeek.dir/src/main.cc.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aaronb/Dev/mine/theNextWeek/src/main.cc > CMakeFiles/theNextWeek.dir/src/main.cc.i

CMakeFiles/theNextWeek.dir/src/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/theNextWeek.dir/src/main.cc.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aaronb/Dev/mine/theNextWeek/src/main.cc -o CMakeFiles/theNextWeek.dir/src/main.cc.s

# Object files for target theNextWeek
theNextWeek_OBJECTS = \
"CMakeFiles/theNextWeek.dir/src/main.cc.o"

# External object files for target theNextWeek
theNextWeek_EXTERNAL_OBJECTS =

theNextWeek: CMakeFiles/theNextWeek.dir/src/main.cc.o
theNextWeek: CMakeFiles/theNextWeek.dir/build.make
theNextWeek: /usr/local/lib/libopencv_dnn.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_gapi.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_highgui.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_ml.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_objdetect.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_photo.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_stitching.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_video.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_videoio.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_imgcodecs.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_calib3d.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_features2d.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_flann.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_imgproc.4.1.1.dylib
theNextWeek: /usr/local/lib/libopencv_core.4.1.1.dylib
theNextWeek: CMakeFiles/theNextWeek.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aaronb/Dev/mine/theNextWeek/cmake-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable theNextWeek"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/theNextWeek.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/theNextWeek.dir/build: theNextWeek

.PHONY : CMakeFiles/theNextWeek.dir/build

CMakeFiles/theNextWeek.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/theNextWeek.dir/cmake_clean.cmake
.PHONY : CMakeFiles/theNextWeek.dir/clean

CMakeFiles/theNextWeek.dir/depend:
	cd /Users/aaronb/Dev/mine/theNextWeek/cmake-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aaronb/Dev/mine/theNextWeek /Users/aaronb/Dev/mine/theNextWeek /Users/aaronb/Dev/mine/theNextWeek/cmake-build /Users/aaronb/Dev/mine/theNextWeek/cmake-build /Users/aaronb/Dev/mine/theNextWeek/cmake-build/CMakeFiles/theNextWeek.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/theNextWeek.dir/depend

