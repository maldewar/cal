# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/waldemar/Projects/Calaveras

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/waldemar/Projects/Calaveras/linux-build

# Include any dependencies generated for this target.
include CMakeFiles/MyGame.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MyGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MyGame.dir/flags.make

CMakeFiles/MyGame.dir/proj.linux/main.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/proj.linux/main.cpp.o: ../proj.linux/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/proj.linux/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/proj.linux/main.cpp.o -c /home/waldemar/Projects/Calaveras/proj.linux/main.cpp

CMakeFiles/MyGame.dir/proj.linux/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/proj.linux/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/proj.linux/main.cpp > CMakeFiles/MyGame.dir/proj.linux/main.cpp.i

CMakeFiles/MyGame.dir/proj.linux/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/proj.linux/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/proj.linux/main.cpp -o CMakeFiles/MyGame.dir/proj.linux/main.cpp.s

CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.requires

CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.provides: CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.provides

CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.provides.build: CMakeFiles/MyGame.dir/proj.linux/main.cpp.o

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o: ../Classes/AppDelegate.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/AppDelegate.cpp

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/AppDelegate.cpp > CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.i

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/AppDelegate.cpp -o CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.s

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o: ../Classes/HelloWorldScene.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/HelloWorldScene.cpp

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/HelloWorldScene.cpp > CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.i

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/HelloWorldScene.cpp -o CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.s

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o: ../Classes/LevelScene.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/LevelScene.cpp

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/LevelScene.cpp > CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.i

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/LevelScene.cpp -o CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.s

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o: ../Classes/util/jsoncpp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/util/jsoncpp.cpp

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/util/jsoncpp.cpp > CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.i

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/util/jsoncpp.cpp -o CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.s

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o: ../Classes/util/b2dJson.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/util/b2dJson.cpp

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/util/b2dJson.cpp > CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.i

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/util/b2dJson.cpp -o CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.s

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o: ../Classes/util/b2dJsonImage.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/util/b2dJsonImage.cpp

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/util/b2dJsonImage.cpp > CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.i

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/util/b2dJsonImage.cpp -o CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.s

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o: ../Classes/util/Box2DDebugDraw.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/util/Box2DDebugDraw.cpp

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/util/Box2DDebugDraw.cpp > CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.i

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/util/Box2DDebugDraw.cpp -o CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.s

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o: ../Classes/layer/BasicRUBELayer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/layer/BasicRUBELayer.cpp

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/layer/BasicRUBELayer.cpp > CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.i

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/layer/BasicRUBELayer.cpp -o CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.s

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o: ../Classes/layer/WorldLevelLayer.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/layer/WorldLevelLayer.cpp

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/layer/WorldLevelLayer.cpp > CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.i

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/layer/WorldLevelLayer.cpp -o CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.s

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o: ../Classes/model/Entity.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/model/Entity.cpp

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/model/Entity.cpp > CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.i

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/model/Entity.cpp -o CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.s

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o: ../Classes/model/Entry.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/model/Entry.cpp

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/model/Entry.cpp > CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.i

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/model/Entry.cpp -o CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.s

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o: CMakeFiles/MyGame.dir/flags.make
CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o: ../Classes/model/Unit.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o -c /home/waldemar/Projects/Calaveras/Classes/model/Unit.cpp

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/waldemar/Projects/Calaveras/Classes/model/Unit.cpp > CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.i

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/waldemar/Projects/Calaveras/Classes/model/Unit.cpp -o CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.s

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.requires:
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.requires

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.provides: CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.requires
	$(MAKE) -f CMakeFiles/MyGame.dir/build.make CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.provides.build
.PHONY : CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.provides

CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.provides.build: CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o

# Object files for target MyGame
MyGame_OBJECTS = \
"CMakeFiles/MyGame.dir/proj.linux/main.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o" \
"CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o"

# External object files for target MyGame
MyGame_EXTERNAL_OBJECTS =

bin/MyGame: CMakeFiles/MyGame.dir/proj.linux/main.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o
bin/MyGame: CMakeFiles/MyGame.dir/build.make
bin/MyGame: lib/libspine.a
bin/MyGame: lib/libbox2d.a
bin/MyGame: lib/libcocostudio.a
bin/MyGame: lib/libcocosbuilder.a
bin/MyGame: lib/libaudio.a
bin/MyGame: lib/libcocos2d.a
bin/MyGame: lib/libextensions.a
bin/MyGame: lib/libchipmunk.a
bin/MyGame: lib/libtinyxml2.a
bin/MyGame: lib/libunzip.a
bin/MyGame: lib/libxxhash.a
bin/MyGame: CMakeFiles/MyGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/MyGame"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MyGame.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MyGame.dir/build: bin/MyGame
.PHONY : CMakeFiles/MyGame.dir/build

CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/proj.linux/main.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/AppDelegate.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/HelloWorldScene.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/LevelScene.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/util/jsoncpp.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/util/b2dJson.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/util/b2dJsonImage.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/util/Box2DDebugDraw.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/layer/BasicRUBELayer.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/layer/WorldLevelLayer.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/model/Entity.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/model/Entry.cpp.o.requires
CMakeFiles/MyGame.dir/requires: CMakeFiles/MyGame.dir/Classes/model/Unit.cpp.o.requires
.PHONY : CMakeFiles/MyGame.dir/requires

CMakeFiles/MyGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MyGame.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MyGame.dir/clean

CMakeFiles/MyGame.dir/depend:
	cd /home/waldemar/Projects/Calaveras/linux-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/waldemar/Projects/Calaveras /home/waldemar/Projects/Calaveras /home/waldemar/Projects/Calaveras/linux-build /home/waldemar/Projects/Calaveras/linux-build /home/waldemar/Projects/Calaveras/linux-build/CMakeFiles/MyGame.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MyGame.dir/depend

