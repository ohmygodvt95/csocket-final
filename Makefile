# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = "/home/quangminh/NetWork Programming/csocket-final"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/quangminh/NetWork Programming/csocket-final"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/quangminh/NetWork Programming/csocket-final/CMakeFiles" "/home/quangminh/NetWork Programming/csocket-final/CMakeFiles/progress.marks"
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/home/quangminh/NetWork Programming/csocket-final/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named client1

# Build rule for target.
client1: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 client1
.PHONY : client1

# fast build rule for target.
client1/fast:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/build
.PHONY : client1/fast

client/find_file/find_file.o: client/find_file/find_file.cpp.o

.PHONY : client/find_file/find_file.o

# target to build an object file
client/find_file/find_file.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/find_file/find_file.cpp.o
.PHONY : client/find_file/find_file.cpp.o

client/find_file/find_file.i: client/find_file/find_file.cpp.i

.PHONY : client/find_file/find_file.i

# target to preprocess a source file
client/find_file/find_file.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/find_file/find_file.cpp.i
.PHONY : client/find_file/find_file.cpp.i

client/find_file/find_file.s: client/find_file/find_file.cpp.s

.PHONY : client/find_file/find_file.s

# target to generate assembly for a file
client/find_file/find_file.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/find_file/find_file.cpp.s
.PHONY : client/find_file/find_file.cpp.s

client/main.o: client/main.cpp.o

.PHONY : client/main.o

# target to build an object file
client/main.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/main.cpp.o
.PHONY : client/main.cpp.o

client/main.i: client/main.cpp.i

.PHONY : client/main.i

# target to preprocess a source file
client/main.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/main.cpp.i
.PHONY : client/main.cpp.i

client/main.s: client/main.cpp.s

.PHONY : client/main.s

# target to generate assembly for a file
client/main.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/main.cpp.s
.PHONY : client/main.cpp.s

client/signin/signin.o: client/signin/signin.cpp.o

.PHONY : client/signin/signin.o

# target to build an object file
client/signin/signin.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signin/signin.cpp.o
.PHONY : client/signin/signin.cpp.o

client/signin/signin.i: client/signin/signin.cpp.i

.PHONY : client/signin/signin.i

# target to preprocess a source file
client/signin/signin.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signin/signin.cpp.i
.PHONY : client/signin/signin.cpp.i

client/signin/signin.s: client/signin/signin.cpp.s

.PHONY : client/signin/signin.s

# target to generate assembly for a file
client/signin/signin.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signin/signin.cpp.s
.PHONY : client/signin/signin.cpp.s

client/signup/signup.o: client/signup/signup.cpp.o

.PHONY : client/signup/signup.o

# target to build an object file
client/signup/signup.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signup/signup.cpp.o
.PHONY : client/signup/signup.cpp.o

client/signup/signup.i: client/signup/signup.cpp.i

.PHONY : client/signup/signup.i

# target to preprocess a source file
client/signup/signup.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signup/signup.cpp.i
.PHONY : client/signup/signup.cpp.i

client/signup/signup.s: client/signup/signup.cpp.s

.PHONY : client/signup/signup.s

# target to generate assembly for a file
client/signup/signup.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/client/signup/signup.cpp.s
.PHONY : client/signup/signup.cpp.s

libs/entity/user.o: libs/entity/user.cpp.o

.PHONY : libs/entity/user.o

# target to build an object file
libs/entity/user.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/entity/user.cpp.o
.PHONY : libs/entity/user.cpp.o

libs/entity/user.i: libs/entity/user.cpp.i

.PHONY : libs/entity/user.i

# target to preprocess a source file
libs/entity/user.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/entity/user.cpp.i
.PHONY : libs/entity/user.cpp.i

libs/entity/user.s: libs/entity/user.cpp.s

.PHONY : libs/entity/user.s

# target to generate assembly for a file
libs/entity/user.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/entity/user.cpp.s
.PHONY : libs/entity/user.cpp.s

libs/functions/string_helper.o: libs/functions/string_helper.cpp.o

.PHONY : libs/functions/string_helper.o

# target to build an object file
libs/functions/string_helper.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/functions/string_helper.cpp.o
.PHONY : libs/functions/string_helper.cpp.o

libs/functions/string_helper.i: libs/functions/string_helper.cpp.i

.PHONY : libs/functions/string_helper.i

# target to preprocess a source file
libs/functions/string_helper.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/functions/string_helper.cpp.i
.PHONY : libs/functions/string_helper.cpp.i

libs/functions/string_helper.s: libs/functions/string_helper.cpp.s

.PHONY : libs/functions/string_helper.s

# target to generate assembly for a file
libs/functions/string_helper.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/functions/string_helper.cpp.s
.PHONY : libs/functions/string_helper.cpp.s

libs/md5/md5.o: libs/md5/md5.cpp.o

.PHONY : libs/md5/md5.o

# target to build an object file
libs/md5/md5.cpp.o:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/md5/md5.cpp.o
.PHONY : libs/md5/md5.cpp.o

libs/md5/md5.i: libs/md5/md5.cpp.i

.PHONY : libs/md5/md5.i

# target to preprocess a source file
libs/md5/md5.cpp.i:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/md5/md5.cpp.i
.PHONY : libs/md5/md5.cpp.i

libs/md5/md5.s: libs/md5/md5.cpp.s

.PHONY : libs/md5/md5.s

# target to generate assembly for a file
libs/md5/md5.cpp.s:
	$(MAKE) -f CMakeFiles/client1.dir/build.make CMakeFiles/client1.dir/libs/md5/md5.cpp.s
.PHONY : libs/md5/md5.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... client1"
	@echo "... client/find_file/find_file.o"
	@echo "... client/find_file/find_file.i"
	@echo "... client/find_file/find_file.s"
	@echo "... client/main.o"
	@echo "... client/main.i"
	@echo "... client/main.s"
	@echo "... client/signin/signin.o"
	@echo "... client/signin/signin.i"
	@echo "... client/signin/signin.s"
	@echo "... client/signup/signup.o"
	@echo "... client/signup/signup.i"
	@echo "... client/signup/signup.s"
	@echo "... libs/entity/user.o"
	@echo "... libs/entity/user.i"
	@echo "... libs/entity/user.s"
	@echo "... libs/functions/string_helper.o"
	@echo "... libs/functions/string_helper.i"
	@echo "... libs/functions/string_helper.s"
	@echo "... libs/md5/md5.o"
	@echo "... libs/md5/md5.i"
	@echo "... libs/md5/md5.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

