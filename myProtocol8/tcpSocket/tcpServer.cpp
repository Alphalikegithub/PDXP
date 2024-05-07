#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/select.h> // 包含 select 函数相关头文件
#include<sys/time.h> // 包含 timeval 结构体相关头文件
#include<cstring> // 包含 memset 函数相关头文件
#include<iostream>
#include"../src/myprotocol.h"

int startup(char* _ip,char* _port);
int myprotoRecv(int sock,char* buf,int max_len);

int main(int argc,char* argv[]) {
    if(argc != 3) {
        printf("Usage:%s local_ip local_port\n", argv[0]);
        return 1;
    }

    // 获取监听 socket 信息
    int listen_sock = startup(argv[1], argv[2]); 

    // 设置结构体，用于接收客户端的 socket 地址结构体
    struct sockaddr_in remote;
    unsigned int len = sizeof(struct sockaddr_in);

    int msgCount = 0; // 消息计数器
    int timeoutCount = 0; // 超时计数器

    while(1) {
        fd_set rfds; // 定义了一个文件描述符集合 rfds
        FD_ZERO(&rfds); // 将其初始化为空集合
        FD_SET(listen_sock, &rfds); // 监听 socket listen_sock 加入到 rfds 中

        struct timeval tv; // 定义了一个 timeval 结构体变量 tv，用于设置超时时间
        tv.tv_sec = 5; // 设置超时时间为 7 秒
        tv.tv_usec = 0;

        /* select() 函数会阻塞等待指定的文件描述符集合上是否有可读事件发生，
        或者超时时间到达。如果超时时间到达，select() 函数会返回 0。
        如果有可读事件发生，select() 函数会返回大于 0 的值 */
        int retval = select(listen_sock + 1, &rfds, NULL, NULL, &tv);
        if (retval == -1) {
            perror("select()");
            exit(EXIT_FAILURE);
        } else if (retval == 0) {
            /* 如果 select() 函数返回值为 0，则说明超时时间到达，
            没有新的客户端连接请求。我们打印相应的提示信息，然后继续下一轮循环，等待新的客户端连接 */
            printf("Timeout occurred! No incoming connection.\n");//说明超时时间到达
            timeoutCount++; // 超时计数器加一
            if (timeoutCount >= 5) { // 如果连续超时计数器达到5次
                printf("Closing communication socket due to continuous timeouts.\n");
                break; // 关闭通信套接字并退出循环
            }
            continue;
        } else {
            /* 函数返回值大于 0，则说明有新的客户端连接请求到达 */
            timeoutCount = 0; // 重置超时计数器为0
            // 开始阻塞方式接收客户端链接
            int sock = accept(listen_sock, (struct sockaddr*)&remote, &len);
            if(sock < 0) {
                printf("client accept failure!\n");
                continue;
            }

            // 开始接收客户端消息
            printf("get connect from %s:%d\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));

            // 循环接收并处理多条消息
            while(1) {
                char buf[1024];
                len = myprotoRecv(sock, buf, 1024);
                if(len <= 0) {
                    printf("Connection closed by client\n");
                    break;
                }
                msgCount++; // 接收到一条消息，计数器加一
            }
            
            printf("Total messages received: %d\n", msgCount);
            close(sock);
        }
    }

    return 0;
}

int startup(char* _ip, char* _port) {
    int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(sock < 0) {
        printf("socket create failure!\n");
        exit(-1);
    }

    // 绑定服务端的地址信息，用于监听当前服务的某网卡、端口
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(_port));
    local.sin_addr.s_addr = inet_addr(_ip);

    int len = sizeof(local);

    if(bind(sock, (struct sockaddr*)&local, len) < 0) {
        printf("socket bind failure!\n");
        exit(-2);
    }

    // 开始监听 sock, 设置同时并发数量
    if(listen(sock, 5) < 0) { // 允许最大连接数量 5
        printf("socket listen failure!\n");
        exit(-3);
    }

    return sock; // 返回文件句柄
}

int myprotoRecv(int sock, char* buf, int max_len) {
    unsigned int len;

    len = recv(sock, buf, sizeof(char) * max_len, 0);

    MyProtoDecode myDecode;
    myDecode.init();

    if(!myDecode.parser(buf, len)) {
        std::cout << "parser msg failed!" << std::endl;
    } else {
        std::cout << "parser msg successful!" << std::endl;
    }

    // 解析消息
    MyProtoMsg* pMsg = NULL;

    while(!myDecode.empty()) {
        pMsg = myDecode.front();
        myProtoMsgPrint(*pMsg);
        myDecode.pop();
    }

    return len;
}

/*
inet_addr 将字符串形式的IP地址 -> 网络字节顺序  的整型值

inet_ntoa 网络字节顺序的整型值 ->字符串形式的IP地址
*/