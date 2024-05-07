#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <queue>
#include "../src/myprotocol.h"
#include "../src/MessageManager.h" // 包含 MessageManager 类的头文件

int myprotoSend(int sock, MyProtoMsg& msg, struct sockaddr_in& serverAddr);
void sendAllMessages(int sock, std::queue<MyProtoMsg>& msgQueue, struct sockaddr_in& serverAddr);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("USage:%s ip port\n", argv[0]);
        return 0;
    }

    // 创建socket并连接服务器
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//注意此处的SOCK_DGRAM
    if (sock < 0) {
        printf("Socket create failure\n");
        return -1;
    }

    // 设置服务器地址信息
    struct sockaddr_in server;
    server.sin_family = AF_INET; //IPV4
    server.sin_port = htons(atoi(argv[2])); //atoi将字符串转数字
    server.sin_addr.s_addr = inet_addr(argv[1]); //不直接使用htonl,因为传入的是字符串IP地址，使用inet_addr正好对字符串IP,转网络大端所用字节序

    // 创建消息队列并添加消息
    std::queue<MyProtoMsg> msgQueue;
    
    // 创建 MessageManager 对象
    MessageManager messageManager;

    // 使用 MessageManager 对象创建并添加消息到队列中
    messageManager.createAndAddMessages(msgQueue);

    // 可以使用消息队列中的消息进行后续的操作，比如发送到服务器端等

    // 发送所有消息
    sendAllMessages(sock, msgQueue, server);

    // 关闭socket
    close(sock);
    return 0;
}

// Function to send a single message
int myprotoSend(int sock, MyProtoMsg& msg, struct sockaddr_in& serverAddr) {
    uint32_t len = 0;
    uint8_t * pData = nullptr;

    /* 打包 */
    MyProtoEncode myEncode;
    pData = myEncode.encode(&msg, len);

    sendto(sock, pData, len, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

    return 0;
}

// Function to send all messages in the queue
void sendAllMessages(int sock, std::queue<MyProtoMsg>& msgQueue, struct sockaddr_in& serverAddr) {
    while (!msgQueue.empty()) {
        MyProtoMsg msg = msgQueue.front();
        myprotoSend(sock, msg, serverAddr);
        msgQueue.pop(); // Remove the sent message from the queue
        sleep(3); // Add a delay between sending messages
    }
}
