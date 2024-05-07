cmake_minimum_required(VERSION 3.0)
project(MyProtocol)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置源文件
set(SOURCES
    main.cpp
    MyProtocol.cpp
    protobuf/cekong.pb.cc
)

# 设置头文件路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 添加可执行文件
add_executable(test ${SOURCES})

# 链接protobuf库
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(test ${PROTOBUF_LIBRARIES})
