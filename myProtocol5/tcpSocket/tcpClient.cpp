#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "../src/myprotocol.h"

int myprotoSend(int sock);

int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		printf("USage:%s ip port\n", argv[0]);
		return 0;
	}

	//开始创建socket
	int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sock < 0)
	{
		printf("socket create failure\n");
		return -1;
	}

	//使用connect与服务器地址，端口连接，需要定义服务端信息：地址结构体
	struct sockaddr_in server;
	server.sin_family = AF_INET; //IPV4
	server.sin_port = htons(atoi(argv[2])); //atoi将字符串转数字
	server.sin_addr.s_addr = inet_addr(argv[1]); //不直接使用htonl,因为传入的是字符串IP地址，使用inet_addr正好对字符串IP,转网络大端所用字节序

	unsigned int len = sizeof(struct sockaddr_in); //获取socket地址结构体长度

	if(connect(sock,(struct sockaddr*)&server,len)<0)
	{
		printf("socket connect failure\n");
		return -2;
	}

	//连接成功，进行数据发送-------------这里可以改为循环发送
	len = myprotoSend(sock);

	close(sock);
	return 0;
}

int myprotoSend(int sock) //-----------这里改为字符串解析，发送自己解析的Json数据
{

	uint32_t len = 0;
    uint8_t * pData = nullptr;

	MyProtoMsg msg1;
	//MyProtoMsg msg2;
	/* 打包 */
	MyProtoEncode myEncode;

	//------放入消息
	// msg1.head.server = 1;
	// msg1.body["op"] = "set";
	// msg1.body["key"] = "id";
	// msg1.body["value"] = "6666";

	msg1.head.MID = 12345; // 设置任务标志
    msg1.head.SID = 987654321; // 设置信源
    msg1.head.DID = 123456789; // 设置信宿
    msg1.head.BID = 987654321; // 设置信息分类标志
    msg1.head.No = 1; // 设置包序号
    msg1.head.FLAG = 0; // 设置信息处理标志
    msg1.head.Backup = 0; // 设置备用字段
    msg1.head.DATE = 2405; // 设置发送日期
    msg1.head.TIME = 225859; // 设置发送时间

    // 使用 Protocol Buffers 格式直接设置第一个消息的协议体字段
    msg1.body.set_current_time(1735227015000);// 设置当前时刻1735227015000;(这个值表示从 Unix 时间戳起点开始的毫秒数)
    msg1.body.set_device_status(1);           // 设置设备状态
    msg1.body.set_azimuth(45.0);              // 设置方位角
    msg1.body.set_elevation(30.0);            // 设置俯仰角
    msg1.body.set_azimuth_offset(100);        // 设置方位脱靶量
    msg1.body.set_elevation_offset(-50);      // 设置俯仰脱靶量
    msg1.body.set_velocity(0.5);              // 设置测速值
    msg1.body.set_distance(1000);             // 设置测距值
    msg1.body.set_brightness(5);              // 设置目标亮度

	pData = myEncode.encode(&msg1,len);

	// msg2.head.server = 2;
	// msg2.body["op"] = "get";
	// msg2.body["key"] = "id";
	// pData = myEncode.encode(&msg2,len);

	return send(sock,pData,len,0);
}