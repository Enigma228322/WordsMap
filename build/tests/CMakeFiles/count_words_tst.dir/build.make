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
include tests/CMakeFiles/count_words_tst.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tests/CMakeFiles/count_words_tst.dir/compiler_depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/count_words_tst.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/count_words_tst.dir/flags.make

tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o: tests/CMakeFiles/count_words_tst.dir/flags.make
tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o: /Users/v.safin/work/count_words_lib/tests/WordsCountServiceTest.cc
tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o: tests/CMakeFiles/count_words_tst.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/v.safin/work/count_words_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o"
	cd /Users/v.safin/work/count_words_lib/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o -MF CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o.d -o CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o -c /Users/v.safin/work/count_words_lib/tests/WordsCountServiceTest.cc

tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.i"
	cd /Users/v.safin/work/count_words_lib/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/v.safin/work/count_words_lib/tests/WordsCountServiceTest.cc > CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.i

tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.s"
	cd /Users/v.safin/work/count_words_lib/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/v.safin/work/count_words_lib/tests/WordsCountServiceTest.cc -o CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.s

# Object files for target count_words_tst
count_words_tst_OBJECTS = \
"CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o"

# External object files for target count_words_tst
count_words_tst_EXTERNAL_OBJECTS =

tests/count_words_tst: tests/CMakeFiles/count_words_tst.dir/WordsCountServiceTest.cc.o
tests/count_words_tst: tests/CMakeFiles/count_words_tst.dir/build.make
tests/count_words_tst: src/libcount_words_lib.a
tests/count_words_tst: lib/libgtest.a
tests/count_words_tst: tests/CMakeFiles/count_words_tst.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/v.safin/work/count_words_lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable count_words_tst"
	cd /Users/v.safin/work/count_words_lib/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/count_words_tst.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/count_words_tst.dir/build: tests/count_words_tst
.PHONY : tests/CMakeFiles/count_words_tst.dir/build

tests/CMakeFiles/count_words_tst.dir/clean:
	cd /Users/v.safin/work/count_words_lib/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/count_words_tst.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/count_words_tst.dir/clean

tests/CMakeFiles/count_words_tst.dir/depend:
	cd /Users/v.safin/work/count_words_lib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/v.safin/work/count_words_lib /Users/v.safin/work/count_words_lib/tests /Users/v.safin/work/count_words_lib/build /Users/v.safin/work/count_words_lib/build/tests /Users/v.safin/work/count_words_lib/build/tests/CMakeFiles/count_words_tst.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tests/CMakeFiles/count_words_tst.dir/depend

