# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/code/PDXP/myProtocol9

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/code/PDXP/myProtocol9/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/server.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o: ../tcpSocket/tcpServer.cpp
CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/PDXP/myProtocol9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o -MF CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o.d -o CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o -c /root/code/PDXP/myProtocol9/tcpSocket/tcpServer.cpp

CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.i"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/PDXP/myProtocol9/tcpSocket/tcpServer.cpp > CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.i

CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.s"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/PDXP/myProtocol9/tcpSocket/tcpServer.cpp -o CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.s

CMakeFiles/server.dir/src/myProtocol.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/src/myProtocol.cpp.o: ../src/myProtocol.cpp
CMakeFiles/server.dir/src/myProtocol.cpp.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/PDXP/myProtocol9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/src/myProtocol.cpp.o"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/src/myProtocol.cpp.o -MF CMakeFiles/server.dir/src/myProtocol.cpp.o.d -o CMakeFiles/server.dir/src/myProtocol.cpp.o -c /root/code/PDXP/myProtocol9/src/myProtocol.cpp

CMakeFiles/server.dir/src/myProtocol.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/src/myProtocol.cpp.i"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/PDXP/myProtocol9/src/myProtocol.cpp > CMakeFiles/server.dir/src/myProtocol.cpp.i

CMakeFiles/server.dir/src/myProtocol.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/src/myProtocol.cpp.s"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/PDXP/myProtocol9/src/myProtocol.cpp -o CMakeFiles/server.dir/src/myProtocol.cpp.s

CMakeFiles/server.dir/protobuf/cekong.pb.cc.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/protobuf/cekong.pb.cc.o: ../protobuf/cekong.pb.cc
CMakeFiles/server.dir/protobuf/cekong.pb.cc.o: CMakeFiles/server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/code/PDXP/myProtocol9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/protobuf/cekong.pb.cc.o"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/server.dir/protobuf/cekong.pb.cc.o -MF CMakeFiles/server.dir/protobuf/cekong.pb.cc.o.d -o CMakeFiles/server.dir/protobuf/cekong.pb.cc.o -c /root/code/PDXP/myProtocol9/protobuf/cekong.pb.cc

CMakeFiles/server.dir/protobuf/cekong.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/protobuf/cekong.pb.cc.i"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/code/PDXP/myProtocol9/protobuf/cekong.pb.cc > CMakeFiles/server.dir/protobuf/cekong.pb.cc.i

CMakeFiles/server.dir/protobuf/cekong.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/protobuf/cekong.pb.cc.s"
	/opt/rh/devtoolset-11/root/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/code/PDXP/myProtocol9/protobuf/cekong.pb.cc -o CMakeFiles/server.dir/protobuf/cekong.pb.cc.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o" \
"CMakeFiles/server.dir/src/myProtocol.cpp.o" \
"CMakeFiles/server.dir/protobuf/cekong.pb.cc.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/tcpSocket/tcpServer.cpp.o
server: CMakeFiles/server.dir/src/myProtocol.cpp.o
server: CMakeFiles/server.dir/protobuf/cekong.pb.cc.o
server: CMakeFiles/server.dir/build.make
server: /usr/local/lib/libprotobuf.so
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/code/PDXP/myProtocol9/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server
.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /root/code/PDXP/myProtocol9/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/code/PDXP/myProtocol9 /root/code/PDXP/myProtocol9 /root/code/PDXP/myProtocol9/build /root/code/PDXP/myProtocol9/build /root/code/PDXP/myProtocol9/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

