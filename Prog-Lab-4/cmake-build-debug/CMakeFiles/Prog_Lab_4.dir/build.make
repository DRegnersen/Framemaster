# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\Users\deofr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\deofr\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-0\212.5457.51\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\deofr\C\Prog-Lab-4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Prog_Lab_4.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Prog_Lab_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Prog_Lab_4.dir/flags.make

CMakeFiles/Prog_Lab_4.dir/main.c.obj: CMakeFiles/Prog_Lab_4.dir/flags.make
CMakeFiles/Prog_Lab_4.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Prog_Lab_4.dir/main.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Prog_Lab_4.dir\main.c.obj -c C:\Users\deofr\C\Prog-Lab-4\main.c

CMakeFiles/Prog_Lab_4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Prog_Lab_4.dir/main.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\deofr\C\Prog-Lab-4\main.c > CMakeFiles\Prog_Lab_4.dir\main.c.i

CMakeFiles/Prog_Lab_4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Prog_Lab_4.dir/main.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\deofr\C\Prog-Lab-4\main.c -o CMakeFiles\Prog_Lab_4.dir\main.c.s

CMakeFiles/Prog_Lab_4.dir/framemaster.c.obj: CMakeFiles/Prog_Lab_4.dir/flags.make
CMakeFiles/Prog_Lab_4.dir/framemaster.c.obj: ../framemaster.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Prog_Lab_4.dir/framemaster.c.obj"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Prog_Lab_4.dir\framemaster.c.obj -c C:\Users\deofr\C\Prog-Lab-4\framemaster.c

CMakeFiles/Prog_Lab_4.dir/framemaster.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Prog_Lab_4.dir/framemaster.c.i"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\deofr\C\Prog-Lab-4\framemaster.c > CMakeFiles\Prog_Lab_4.dir\framemaster.c.i

CMakeFiles/Prog_Lab_4.dir/framemaster.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Prog_Lab_4.dir/framemaster.c.s"
	C:\msys64\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\deofr\C\Prog-Lab-4\framemaster.c -o CMakeFiles\Prog_Lab_4.dir\framemaster.c.s

# Object files for target Prog_Lab_4
Prog_Lab_4_OBJECTS = \
"CMakeFiles/Prog_Lab_4.dir/main.c.obj" \
"CMakeFiles/Prog_Lab_4.dir/framemaster.c.obj"

# External object files for target Prog_Lab_4
Prog_Lab_4_EXTERNAL_OBJECTS =

Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/main.c.obj
Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/framemaster.c.obj
Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/build.make
Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/linklibs.rsp
Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/objects1.rsp
Prog_Lab_4.exe: CMakeFiles/Prog_Lab_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Prog_Lab_4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Prog_Lab_4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Prog_Lab_4.dir/build: Prog_Lab_4.exe
.PHONY : CMakeFiles/Prog_Lab_4.dir/build

CMakeFiles/Prog_Lab_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Prog_Lab_4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Prog_Lab_4.dir/clean

CMakeFiles/Prog_Lab_4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\deofr\C\Prog-Lab-4 C:\Users\deofr\C\Prog-Lab-4 C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug C:\Users\deofr\C\Prog-Lab-4\cmake-build-debug\CMakeFiles\Prog_Lab_4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Prog_Lab_4.dir/depend

