cmake_minimum_required(VERSION 3.0)
project(MyProtocol)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置源文件列表
set(SOURCES_COMMON
    src/myProtocol.cpp
    protobuf/cekong.pb.cc
)

set(SOURCES_SERVER
    tcpSocket/tcpServer.cpp
    ${SOURCES_COMMON}
)

set(SOURCES_CLIENT
    tcpSocket/tcpClient.cpp
    src/MessageManager.cpp  # 添加 MessageManager.cpp
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
