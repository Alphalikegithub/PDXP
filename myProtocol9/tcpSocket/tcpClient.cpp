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

int myprotoSend(int sock, MyProtoMsg& msg);
void sendAllMessages(int sock, std::queue<MyProtoMsg>& msgQueue);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("USage:%s ip port\n", argv[0]);
        return 0;
    }

    // 创建socket并连接服务器
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock < 0) {
        printf("socket create failure\n");
        return -1;
    }

    // 使用connect与服务器地址，端口连接，需要定义服务端信息：地址结构体
    struct sockaddr_in server;
    server.sin_family = AF_INET; //IPV4
    server.sin_port = htons(atoi(argv[2])); //atoi将字符串转数字
    server.sin_addr.s_addr = inet_addr(argv[1]); //不直接使用htonl,因为传入的是字符串IP地址，使用inet_addr正好对字符串IP,转网络大端所用字节序

    unsigned int len = sizeof(struct sockaddr_in); //获取socket地址结构体长度

    if (connect(sock, (struct sockaddr*)&server, len) < 0) {
        printf("socket connect failure\n");
        return -2;
    }

    // 创建消息队列并添加消息
    std::queue<MyProtoMsg> msgQueue;
    
    // 创建 MessageManager 对象
    MessageManager messageManager;

    /* ***************新增代码******************* */
    // 指定要生成的消息数量
    int numMessages = 10;
    /* ***************************************** */

    /* // 使用 MessageManager 对象创建并添加消息到队列中
    messageManager.createAndAddMessages(msgQueue); */

    // 使用 MessageManager 对象创建并添加指定数量的消息到队列中
    messageManager.createAndAddMessages(msgQueue, numMessages);

    // 可以使用消息队列中的消息进行后续的操作，比如发送到服务器端等

    // 发送所有消息
    sendAllMessages(sock, msgQueue);

    // 关闭socket
    close(sock);
    return 0;
}



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
        sleep(3); // Add a delay between sending messages
    }
}
