#ifndef __MYPROTOCOL_H
#define __MYPROTOCOL_H
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <queue>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include "../protobuf/cekong.pb.h"


#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")
typedef int socklen_t ;
#else
#include <arpa/inet.h>
#endif

using namespace std;

//最大包大小限制（10MB）
const uint32_t MY_PROTO_MAX_SIZE = 10 * 1024 * 1024; //10MB
const uint32_t MY_PROTO_HEAD_SIZE = 32;

//协议解析的状态
typedef enum MyProtoParserStatus
{
    ON_PARSER_INIT = 0,//初始状态
    ON_PARSER_HAED = 1,//解析头部
    ON_PARSER_BODY = 2,//解析数据
}MyProtoParserStatus;



/*
    协议头部
 */
struct MyProtoHead
{
    uint8_t  VER;           // 版本号：1字节
    uint16_t MID;           // 任务标志：2字节
    uint32_t SID;           // 信源：4字节
    uint32_t DID;           // 信宿：4字节
    uint32_t BID;           // 信息分类标志：4字节
    uint32_t No;            // 包序号：4字节
    uint8_t  FLAG;          // 信息处理标志：1字节
    uint32_t Backup;        // 备用：4字节
    uint16_t DATE;          // 发送日期：2字节
    uint32_t TIME;          // 发送时间：4字节
    /* uint16_t LEN;           // 数据域长度：2字节 */
    uint16_t LEN;           // 协议长度（协议头长度+变长json协议体长度）
};

/*
    协议消息体
 */
struct MyProtoMsg
{
    MyProtoHead head;    // 协议头
    MyMessageBody body;  // Protocol Buffers 格式的协议体
    //Json::Value body;   //协议体
};


//----------------------------------公共函数----------------------------------
//打印协议数据信息
void myProtoMsgPrint(MyProtoMsg & msg);

//协议封装类
class MyProtoEncode
{
public:
	//协议消息体封装函数：传入的pMsg里面只有部分数据，比如Json协议体，服务号，对消息编码后会修改长度信息，这时需要重新编码协议
	 uint8_t * encode(MyProtoMsg * pMsg, uint32_t & len); //返回长度信息，用于后面socket发送数据
private:
	//协议头封装函数
	void headEncode(uint8_t * pData, MyProtoMsg * pMsg);
};



//协议解析类
class MyProtoDecode
{
public:
	void init(); //初始化协议解析状态
	void clear(); //清空解析好的消息队列
	bool empty(); //判断解析好的消息队列是否为空
	void pop();  //出队一个消息

	MyProtoMsg* front(); //获取一个解析好的消息
	bool parser(void* data,size_t len); //从网络字节流中解析出来协议消息，len是网络中的字节流长度，通过socket可以获取
private:
    //用于解析消息头
    bool parserHead(uint8_t ** curData, uint32_t & curLen, 
            uint32_t & parserLen, bool & parserBreak);
	//用于解析消息体
    bool parserBody(uint8_t ** curData, uint32_t & curLen, 
        uint32_t & parserLen, bool & parserBreak);
private:
	MyProtoMsg mCurMsg; //当前解析中的协议消息体
	queue<MyProtoMsg*> mMsgQ; //解析好的协议消息队列
	vector<uint8_t> mCurReserved; //未解析的网络字节流，可以缓存所有没有解析的数据（按字节）
	MyProtoParserStatus mCurParserStatus; //当前接受方解析状态
};

#endif