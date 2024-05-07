将消息发送逻辑提取到一个单独的函数中
在myProtocol7中引入了队列

如果有多条消息需要发送，你可以考虑使用数据结构来存储这些消息，然后按需发送。一种常见的数据结构是队列，你可以将消息依次添加到队列中，然后逐个发送。这样可以确保消息按照顺序发送，并且可以方便地管理和控制消息的发送。

另外，如果你需要持久化存储消息并且需要更灵活的查询和管理功能，你可以考虑使用数据库。在数据库中，你可以为每条消息定义一个表，然后将消息存储在相应的表中。这样可以方便地进行消息的检索、修改和删除，并且可以确保消息的持久化存储。常见的数据库包括关系型数据库（如MySQL、PostgreSQL）和NoSQL数据库（如MongoDB、Redis），你可以根据具体需求选择合适的数据库类型。

在C++中，你可以使用标准库提供的队列容器 `std::queue` 来管理消息队列。下面是一个简单的示例代码，演示了如何在客户端代码中使用队列来存储消息并按需发送：

```cpp
#include <iostream>
#include <queue>
#include <unistd.h> // for sleep
#include "../src/myprotocol.h"

// Function to send a single message
int myprotoSend(int sock, MyProtoMsg& msg) {
    uint32_t len = 0;
    uint8_t * pData = nullptr;

    /* 打包 */
    MyProtoEncode myEncode;
    pData = myEncode.encode(&msg, len);

    send(sock, pData, len, 0);

    return 0;
}

// Function to send all messages in the queue
void sendAllMessages(int sock, std::queue<MyProtoMsg>& msgQueue) {
    while (!msgQueue.empty()) {
        MyProtoMsg msg = msgQueue.front();
        myprotoSend(sock, msg);
        msgQueue.pop(); // Remove the sent message from the queue
        sleep(1); // Add a delay between sending messages
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage:" << argv[0] << " ip port\n";
        return 0;
    }

    // 创建socket并连接服务器
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        std::cout << "socket create failure\n";
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET; 
    server.sin_port = htons(atoi(argv[2])); 
    server.sin_addr.s_addr = inet_addr(argv[1]);

    unsigned int len = sizeof(struct sockaddr_in); 

    if (connect(sock, (struct sockaddr*)&server, len) < 0) {
        std::cout << "socket connect failure\n";
        return -2;
    }

    // 创建消息队列并添加消息
    std::queue<MyProtoMsg> msgQueue;
    MyProtoMsg msg1, msg2;

    // 添加消息到队列
    // 注意：这里需要根据实际需求添加需要发送的消息
    // 这里只是一个简单示例，实际应用中需要根据业务逻辑添加消息
    msgQueue.push(msg1);
    msgQueue.push(msg2);

    // 发送所有消息
    sendAllMessages(sock, msgQueue);

    // 关闭socket
    close(sock);
    
    return 0;
}
```

在这个示例中，我们使用了 `std::queue<MyProtoMsg>` 来存储消息队列。在 `sendAllMessages` 函数中，我们不断从队列中取出消息发送，直到队列为空。这样就可以实现按需发送消息，并确保消息按照顺序发送。