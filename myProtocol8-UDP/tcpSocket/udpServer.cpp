#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<cstring>
#include<iostream>
#include"../src/myprotocol.h"

int startup(char* _ip, char* _port);
int myprotoRecv(int sock, char* buf, int max_len, struct sockaddr_in& remoteAddr);

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Usage:%s local_ip local_port\n", argv[0]);
        return 1;
    }

    // 获取监听 socket 信息
    int listen_sock = startup(argv[1], argv[2]); 

    unsigned int len = sizeof(struct sockaddr_in);

    int msgCount = 0; // 消息计数器

    while(1) {
        struct sockaddr_in remote; // 用于接收客户端的地址信息
        char buf[1024];

        int len = myprotoRecv(listen_sock, buf, 1024, remote);
        if(len <= 0) {
            printf("Error receiving message\n");
            continue;
        }

        /* UDP服务器无需调用accept函数或创建新的连接，因为UDP是无连接的。 */

        // 开始接收客户端消息
        printf("Received message from %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));

        // 解析消息
        MyProtoDecode myDecode;
        myDecode.init();

        if(!myDecode.parser(buf, len)) {
            std::cout << "Parser msg failed!" << std::endl;
        } else {
            std::cout << "Parser msg successful!" << std::endl;
        }

        // 解析消息
        MyProtoMsg* pMsg = NULL;

        while(!myDecode.empty()) {
            pMsg = myDecode.front();
            myProtoMsgPrint(*pMsg);
            myDecode.pop();
        }

        msgCount++; // 消息计数器加一
        printf("Total messages received: %d\n", msgCount);
    }

    return 0;
}

int startup(char* _ip, char* _port) {
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sock < 0) {
        printf("Socket create failure!\n");
        exit(-1);
    }

    // 绑定服务端的地址信息，用于监听当前服务的某网卡、端口
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(_port));
    local.sin_addr.s_addr = inet_addr(_ip);

    int len = sizeof(local);

    if(bind(sock, (struct sockaddr*)&local, len) < 0) {
        printf("Socket bind failure!\n");
        exit(-2);
    }

    /* 在UDP服务器中，无需监听连接请求，直接通过recvfrom函数接收数据报文 */

    return sock; // 返回文件句柄
}

int myprotoRecv(int sock, char* buf, int max_len, struct sockaddr_in& remoteAddr) {
    unsigned int len;

    len = recvfrom(sock, buf, sizeof(char) * max_len, 0, (struct sockaddr*)&remoteAddr, &len);
    return len;
}
