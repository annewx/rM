# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /home/anne/Downloads/CLion-2023.1.5/clion-2023.1.5/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /home/anne/Downloads/CLion-2023.1.5/clion-2023.1.5/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/anne/hik_camera

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anne/hik_camera/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/hik_camera.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/hik_camera.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/hik_camera.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hik_camera.dir/flags.make

CMakeFiles/hik_camera.dir/HikCam.cpp.o: CMakeFiles/hik_camera.dir/flags.make
CMakeFiles/hik_camera.dir/HikCam.cpp.o: /home/anne/hik_camera/HikCam.cpp
CMakeFiles/hik_camera.dir/HikCam.cpp.o: CMakeFiles/hik_camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anne/hik_camera/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hik_camera.dir/HikCam.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hik_camera.dir/HikCam.cpp.o -MF CMakeFiles/hik_camera.dir/HikCam.cpp.o.d -o CMakeFiles/hik_camera.dir/HikCam.cpp.o -c /home/anne/hik_camera/HikCam.cpp

CMakeFiles/hik_camera.dir/HikCam.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hik_camera.dir/HikCam.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anne/hik_camera/HikCam.cpp > CMakeFiles/hik_camera.dir/HikCam.cpp.i

CMakeFiles/hik_camera.dir/HikCam.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hik_camera.dir/HikCam.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anne/hik_camera/HikCam.cpp -o CMakeFiles/hik_camera.dir/HikCam.cpp.s

CMakeFiles/hik_camera.dir/main.cpp.o: CMakeFiles/hik_camera.dir/flags.make
CMakeFiles/hik_camera.dir/main.cpp.o: /home/anne/hik_camera/main.cpp
CMakeFiles/hik_camera.dir/main.cpp.o: CMakeFiles/hik_camera.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anne/hik_camera/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hik_camera.dir/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/hik_camera.dir/main.cpp.o -MF CMakeFiles/hik_camera.dir/main.cpp.o.d -o CMakeFiles/hik_camera.dir/main.cpp.o -c /home/anne/hik_camera/main.cpp

CMakeFiles/hik_camera.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hik_camera.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/anne/hik_camera/main.cpp > CMakeFiles/hik_camera.dir/main.cpp.i

CMakeFiles/hik_camera.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hik_camera.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/anne/hik_camera/main.cpp -o CMakeFiles/hik_camera.dir/main.cpp.s

# Object files for target hik_camera
hik_camera_OBJECTS = \
"CMakeFiles/hik_camera.dir/HikCam.cpp.o" \
"CMakeFiles/hik_camera.dir/main.cpp.o"

# External object files for target hik_camera
hik_camera_EXTERNAL_OBJECTS =

hik_camera: CMakeFiles/hik_camera.dir/HikCam.cpp.o
hik_camera: CMakeFiles/hik_camera.dir/main.cpp.o
hik_camera: CMakeFiles/hik_camera.dir/build.make
hik_camera: /usr/local/lib/libopencv_dnn.so.4.5.0
hik_camera: /usr/local/lib/libopencv_highgui.so.4.5.0
hik_camera: /usr/local/lib/libopencv_ml.so.4.5.0
hik_camera: /usr/local/lib/libopencv_objdetect.so.4.5.0
hik_camera: /usr/local/lib/libopencv_photo.so.4.5.0
hik_camera: /usr/local/lib/libopencv_stitching.so.4.5.0
hik_camera: /usr/local/lib/libopencv_video.so.4.5.0
hik_camera: /usr/local/lib/libopencv_videoio.so.4.5.0
hik_camera: /usr/local/lib/libopencv_imgcodecs.so.4.5.0
hik_camera: /usr/local/lib/libopencv_calib3d.so.4.5.0
hik_camera: /usr/local/lib/libopencv_features2d.so.4.5.0
hik_camera: /usr/local/lib/libopencv_flann.so.4.5.0
hik_camera: /usr/local/lib/libopencv_imgproc.so.4.5.0
hik_camera: /usr/local/lib/libopencv_core.so.4.5.0
hik_camera: CMakeFiles/hik_camera.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anne/hik_camera/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hik_camera"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hik_camera.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hik_camera.dir/build: hik_camera
.PHONY : CMakeFiles/hik_camera.dir/build

CMakeFiles/hik_camera.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hik_camera.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hik_camera.dir/clean

CMakeFiles/hik_camera.dir/depend:
	cd /home/anne/hik_camera/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anne/hik_camera /home/anne/hik_camera /home/anne/hik_camera/cmake-build-debug /home/anne/hik_camera/cmake-build-debug /home/anne/hik_camera/cmake-build-debug/CMakeFiles/hik_camera.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/hik_camera.dir/depend
