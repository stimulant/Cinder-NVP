# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_SOURCE_DIR = /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release

# Include any dependencies generated for this target.
include CMakeFiles/NVPTextStressSampleLinux.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NVPTextStressSampleLinux.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NVPTextStressSampleLinux.dir/flags.make

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o: CMakeFiles/NVPTextStressSampleLinux.dir/flags.make
CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o: ../../src/NVPTextStressSample.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o -c /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/NVPTextStressSample.cpp

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/NVPTextStressSample.cpp > CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.i

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/NVPTextStressSample.cpp -o CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.s

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.requires:
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.requires

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.provides: CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.requires
	$(MAKE) -f CMakeFiles/NVPTextStressSampleLinux.dir/build.make CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.provides.build
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.provides

CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.provides.build: CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o: CMakeFiles/NVPTextStressSampleLinux.dir/flags.make
CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o: ../../src/Globals.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o -c /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Globals.cpp

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Globals.cpp > CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.i

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Globals.cpp -o CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.s

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.requires:
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.requires

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.provides: CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.requires
	$(MAKE) -f CMakeFiles/NVPTextStressSampleLinux.dir/build.make CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.provides.build
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.provides

CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.provides.build: CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o: CMakeFiles/NVPTextStressSampleLinux.dir/flags.make
CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o: ../../src/Cinder-NVP/NVPTextBoxTest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o -c /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Cinder-NVP/NVPTextBoxTest.cpp

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Cinder-NVP/NVPTextBoxTest.cpp > CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.i

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/src/Cinder-NVP/NVPTextBoxTest.cpp -o CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.s

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.requires:
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.requires

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.provides: CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/NVPTextStressSampleLinux.dir/build.make CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.provides.build
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.provides

CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.provides.build: CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o: CMakeFiles/NVPTextStressSampleLinux.dir/flags.make
CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o: /home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o -c /home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp > CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.i

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp -o CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.s

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.requires:
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.requires

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.provides: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.requires
	$(MAKE) -f CMakeFiles/NVPTextStressSampleLinux.dir/build.make CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.provides.build
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.provides

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.provides.build: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o: CMakeFiles/NVPTextStressSampleLinux.dir/flags.make
CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o: /home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o -c /home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp > CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.i

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp -o CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.s

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.requires:
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.requires

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.provides: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.requires
	$(MAKE) -f CMakeFiles/NVPTextStressSampleLinux.dir/build.make CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.provides.build
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.provides

CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.provides.build: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o

# Object files for target NVPTextStressSampleLinux
NVPTextStressSampleLinux_OBJECTS = \
"CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o" \
"CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o" \
"CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o" \
"CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o" \
"CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o"

# External object files for target NVPTextStressSampleLinux
NVPTextStressSampleLinux_EXTERNAL_OBJECTS =

bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/build.make
bin/NVPTextStressSampleLinux: /home/ubuntu/Cinder/CMake/libs/libcinderRelease.a
bin/NVPTextStressSampleLinux: /home/ubuntu/Cinder/CMake/libs/libglfw3.a
bin/NVPTextStressSampleLinux: CMakeFiles/NVPTextStressSampleLinux.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable bin/NVPTextStressSampleLinux"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NVPTextStressSampleLinux.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NVPTextStressSampleLinux.dir/build: bin/NVPTextStressSampleLinux
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/build

CMakeFiles/NVPTextStressSampleLinux.dir/requires: CMakeFiles/NVPTextStressSampleLinux.dir/src/NVPTextStressSample.cpp.o.requires
CMakeFiles/NVPTextStressSampleLinux.dir/requires: CMakeFiles/NVPTextStressSampleLinux.dir/src/Globals.cpp.o.requires
CMakeFiles/NVPTextStressSampleLinux.dir/requires: CMakeFiles/NVPTextStressSampleLinux.dir/src/Cinder-NVP/NVPTextBoxTest.cpp.o.requires
CMakeFiles/NVPTextStressSampleLinux.dir/requires: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPFont.cpp.o.requires
CMakeFiles/NVPTextStressSampleLinux.dir/requires: CMakeFiles/NVPTextStressSampleLinux.dir/home/ubuntu/Cinder-NVP/src/src/NVPTextBox.cpp.o.requires
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/requires

CMakeFiles/NVPTextStressSampleLinux.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NVPTextStressSampleLinux.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/clean

CMakeFiles/NVPTextStressSampleLinux.dir/depend:
	cd /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release /home/ubuntu/Cinder-NVP/samples/NVPTextStressSample/linux/release/CMakeFiles/NVPTextStressSampleLinux.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NVPTextStressSampleLinux.dir/depend
