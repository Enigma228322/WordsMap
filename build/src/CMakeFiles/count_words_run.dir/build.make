# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/v.safin/work/count_words_lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/v.safin/work/count_words_lib/build

# Include any dependencies generated for this target.
include src/CMakeFiles/count_words_run.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/count_words_run.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/count_words_run.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/count_words_run.dir/flags.make

src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o: src/CMakeFiles/count_words_run.dir/flags.make
src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o: /Users/v.safin/work/count_words_lib/src/WordsCountService/WordsCountServiceImpl.cc
src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o: src/CMakeFiles/count_words_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/v.safin/work/count_words_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o -MF CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o.d -o CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o -c /Users/v.safin/work/count_words_lib/src/WordsCountService/WordsCountServiceImpl.cc

src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.i"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/v.safin/work/count_words_lib/src/WordsCountService/WordsCountServiceImpl.cc > CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.i

src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.s"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/v.safin/work/count_words_lib/src/WordsCountService/WordsCountServiceImpl.cc -o CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.s

src/CMakeFiles/count_words_run.dir/main.cc.o: src/CMakeFiles/count_words_run.dir/flags.make
src/CMakeFiles/count_words_run.dir/main.cc.o: /Users/v.safin/work/count_words_lib/src/main.cc
src/CMakeFiles/count_words_run.dir/main.cc.o: src/CMakeFiles/count_words_run.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/v.safin/work/count_words_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/count_words_run.dir/main.cc.o"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/count_words_run.dir/main.cc.o -MF CMakeFiles/count_words_run.dir/main.cc.o.d -o CMakeFiles/count_words_run.dir/main.cc.o -c /Users/v.safin/work/count_words_lib/src/main.cc

src/CMakeFiles/count_words_run.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/count_words_run.dir/main.cc.i"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/v.safin/work/count_words_lib/src/main.cc > CMakeFiles/count_words_run.dir/main.cc.i

src/CMakeFiles/count_words_run.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/count_words_run.dir/main.cc.s"
	cd /Users/v.safin/work/count_words_lib/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/v.safin/work/count_words_lib/src/main.cc -o CMakeFiles/count_words_run.dir/main.cc.s

# Object files for target count_words_run
count_words_run_OBJECTS = \
"CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o" \
"CMakeFiles/count_words_run.dir/main.cc.o"

# External object files for target count_words_run
count_words_run_EXTERNAL_OBJECTS =

src/count_words_run: src/CMakeFiles/count_words_run.dir/WordsCountService/WordsCountServiceImpl.cc.o
src/count_words_run: src/CMakeFiles/count_words_run.dir/main.cc.o
src/count_words_run: src/CMakeFiles/count_words_run.dir/build.make
src/count_words_run: src/CMakeFiles/count_words_run.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/v.safin/work/count_words_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable count_words_run"
	cd /Users/v.safin/work/count_words_lib/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/count_words_run.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/count_words_run.dir/build: src/count_words_run
.PHONY : src/CMakeFiles/count_words_run.dir/build

src/CMakeFiles/count_words_run.dir/clean:
	cd /Users/v.safin/work/count_words_lib/build/src && $(CMAKE_COMMAND) -P CMakeFiles/count_words_run.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/count_words_run.dir/clean

src/CMakeFiles/count_words_run.dir/depend:
	cd /Users/v.safin/work/count_words_lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/v.safin/work/count_words_lib /Users/v.safin/work/count_words_lib/src /Users/v.safin/work/count_words_lib/build /Users/v.safin/work/count_words_lib/build/src /Users/v.safin/work/count_words_lib/build/src/CMakeFiles/count_words_run.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/count_words_run.dir/depend

