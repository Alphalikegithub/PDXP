在myProtocol5中：
引入了tcp套接字通信
并对原来的目录结构做了优化：
.
├── build
├── CMakeLists.txt
├── protobuf
│   ├── cc.cc
│   ├── cekong.pb.cc
│   ├── cekong.pb.h
│   ├── cekong.proto
│   └── note.txt
├── README.md
├── run.txt
├── src
│   ├── MyProtocol.cpp
│   └── myprotocol.h
└── tcpSocket
    ├── tcpClient.cpp
    └── tcpServer.cpp