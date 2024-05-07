# cmake_minimum_required(VERSION 3.0)
# project(MyProtocol)

# # 设置C++标准
# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 设置源文件
# set(SOURCES
#     src/MyProtocol.cpp
#     protobuf/cekong.pb.cc
#     tcpSocket/tcpServer.cpp
#     tcpSocket/tcpClient.cpp
# )

# # 设置头文件路径
# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/protobuf)

# # 添加可执行文件
# add_executable(server  src/MyProtocol.cpp protobuf/cekong.pb.cc tcpSocket/tcpServer.cpp)
# add_executable(client  src/MyProtocol.cpp protobuf/cekong.pb.cc tcpSocket/tcpClient.cpp)

# # 链接protobuf库
# find_package(Protobuf REQUIRED)
# include_directories(${PROTOBUF_INCLUDE_DIRS})
# target_link_libraries(server ${PROTOBUF_LIBRARIES})
# target_link_libraries(client ${PROTOBUF_LIBRARIES})


cmake_minimum_required(VERSION 3.0)
project(MyProtocol)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置源文件列表
set(SOURCES_COMMON
    src/MyProtocol.cpp
    protobuf/cekong.pb.cc
)

set(SOURCES_SERVER
    tcpSocket/tcpServer.cpp
    ${SOURCES_COMMON}
)

set(SOURCES_CLIENT
    tcpSocket/tcpClient.cpp
    ${SOURCES_COMMON}
)

# 添加可执行文件
add_executable(server ${SOURCES_SERVER})
add_executable(client ${SOURCES_CLIENT})

# 链接protobuf库
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
target_link_libraries(server ${PROTOBUF_LIBRARIES})
target_link_libraries(client ${PROTOBUF_LIBRARIES})

