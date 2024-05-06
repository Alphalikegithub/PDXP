#include <stdint.h>
#include <stdio.h>
#include <queue>
#include <vector>
#include <iostream>
#include <string.h>
#include "jsoncpp/json.h"
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib,"Ws2_32.lib")
typedef int socklen_t ;
#else
#include <arpa/inet.h>
#endif

using namespace std;
/* ----------const uint8_t MY_PROTO_MAGIC = 88; */
//最大包大小限制（10MB）
const uint32_t MY_PROTO_MAX_SIZE = 10 * 1024 * 1024; //10MB
/* const uint32_t MY_PROTO_HEAD_SIZE = 8; */
const uint32_t MY_PROTO_HEAD_SIZE = 32;
typedef enum MyProtoParserStatus
{
    ON_PARSER_INIT = 0,
    ON_PARSER_HAED = 1,
    ON_PARSER_BODY = 2,
}MyProtoParserStatus;

/*
    协议头
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
    MyProtoHead head;   //协议头
    Json::Value body;   //协议体
};

void myProtoMsgPrint(MyProtoMsg & msg)
{
    string jsonStr = "";
    Json::FastWriter fWriter;
    jsonStr = fWriter.write(msg.body);
    printf("Head[VER=%d,MID=%d,SID=%d,DID=%d,BID=%d,Number=%d,FLAG=%d,BACKUP=%d,DATE=%d,TIME=%d,LEN=%d],Body:%s\n",
           msg.head.VER, msg.head.MID, msg.head.SID, msg.head.DID, msg.head.BID, msg.head.No,
           msg.head.FLAG, msg.head.Backup, msg.head.DATE, msg.head.TIME, msg.head.LEN, jsonStr.c_str());
}



/*
    MyProto打包类
 */
class MyProtoEnCode
{
public:
    //协议消息体打包函数
    uint8_t * encode(MyProtoMsg * pMsg, uint32_t & len);
private:
    //协议头打包函数
    void headEncode(uint8_t * pData, MyProtoMsg * pMsg);
};


void MyProtoEnCode::headEncode(uint8_t * pData, MyProtoMsg * pMsg)
{
    //*pData = pMsg->head.VER;
    //设置协议头版本号为1
    *pData = 1; 
    ++pData;//向前移动一个字节位置到任务标志MID
    *(uint16_t *)pData = htons(pMsg->head.MID);
    pData += 2;//向前移动两个个字节位置，到信源SID字段（32位大小）
    *(uint32_t *)pData = htonl(pMsg->head.SID);
    pData += 4;
    *(uint32_t *)pData = htonl(pMsg->head.DID);
    pData += 4;
    *(uint32_t *)pData = htonl(pMsg->head.BID);
    pData += 4;
    *(uint32_t *)pData = htonl(pMsg->head.No);
    pData += 4;
    *pData = pMsg->head.FLAG;
    ++pData;
    *(uint32_t *)pData = htonl(pMsg->head.Backup);
    pData += 4;
    *(uint16_t *)pData = htons(pMsg->head.DATE);
    pData += 2;
    *(uint32_t *)pData = htonl(pMsg->head.TIME);
    pData += 4;
    *(uint16_t *)pData = htons(pMsg->head.LEN);
}

uint8_t* MyProtoEnCode::encode(MyProtoMsg* pMsg, uint32_t& len)
{
    uint8_t* pData = NULL;
    Json::FastWriter fWriter;

    // 序列化协议体为 JSON 字符串
    string bodyStr = fWriter.write(pMsg->body);

    // 计算协议消息序列化后的总长度（包括头部和体部）
    len = MY_PROTO_HEAD_SIZE + static_cast<uint32_t>(bodyStr.size());

    // 设置消息头部的长度字段
    pMsg->head.LEN = static_cast<uint16_t>(len);

    // 分配空间
    pData = new uint8_t[len];

    // 打包协议头
    headEncode(pData, pMsg);

    // 打包协议体
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData;
}




/*
    MyProto解包类
 */
class MyProtoDeCode
{
public:
    void init();
    void clear();
    bool parser(void * data, size_t len);
    bool empty();
    MyProtoMsg * front();
    void pop();
private:
    bool parserHead(uint8_t ** curData, uint32_t & curLen, 
        uint32_t & parserLen, bool & parserBreak);
    bool parserBody(uint8_t ** curData, uint32_t & curLen, 
        uint32_t & parserLen, bool & parserBreak);
private:
    MyProtoMsg mCurMsg;                     //当前解析中的协议消息体
    queue<MyProtoMsg *> mMsgQ;              //解析好的协议消息队列
    vector<uint8_t> mCurReserved;           //未解析的网络字节流
    MyProtoParserStatus mCurParserStatus;   //当前解析状态
};

void MyProtoDeCode::init()
{
    mCurParserStatus = ON_PARSER_INIT;
}

//清空解析好的消息队列
void MyProtoDeCode::clear()
{
    MyProtoMsg * pMsg = NULL;
    while (!mMsgQ.empty())
    {
        pMsg = mMsgQ.front();
        delete pMsg;
        mMsgQ.pop();
    }
}

bool MyProtoDeCode::parserHead(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; // 由于数据没有头部长，没办法解析，跳出即可
        return true;//但是数据还是有用的，我们没有发现出错，返回true。等待一会数据到了，再解析头部。由于标志没变，一会还是解析头部
    }
    uint8_t * pData = *curData;
    //从网络字节流中，解析出来协议格式数据。保存在MyProtoMsg mCurMsg; //当前解析中的协议消息体
	//解析出来版本号
    mCurMsg.head.VER = *pData;
    pData++;
    mCurMsg.head.MID = ntohs(*(uint16_t*)pData);
    pData += 2;
    mCurMsg.head.SID = ntohl(*(uint32_t*)pData);
    pData += 4;
    mCurMsg.head.DID = ntohl(*(uint32_t*)pData);
    pData += 4;
    mCurMsg.head.BID = ntohl(*(uint32_t*)pData);
    pData += 4;
    mCurMsg.head.No = ntohl(*(uint32_t*)pData);
    pData += 4;
    mCurMsg.head.FLAG = *pData;
    pData++;
    mCurMsg.head.Backup = ntohl(*(uint32_t*)pData);
    pData += 4;
    mCurMsg.head.DATE = ntohs(*(uint16_t*)pData);
    pData += 2;
    mCurMsg.head.TIME = ntohl(*(uint32_t*)pData);
    pData += 4;
    // 计算协议体长度，整个消息长度减去头部长度
    mCurMsg.head.LEN = ntohs(*(uint16_t*)(pData)); // 根据协议头部的定义获取长度字段
    //判断数据长度是否超过指定的大小，异常大包，则返回解析失败
    if (mCurMsg.head.LEN > MY_PROTO_MAX_SIZE)
    {
        return false;
    }
    //解析指针向前移动MY_PROTO_HEAD_SIZE字节，移动到消息体位置,跳过消息头大小
    (*curData) += MY_PROTO_HEAD_SIZE;
    curLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    mCurParserStatus = ON_PARSER_HAED;// 设置解析状态
    return true;
}

//用于解析消息体
bool MyProtoDeCode::parserBody(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    uint32_t jsonSize = mCurMsg.head.LEN - MY_PROTO_HEAD_SIZE;

    if (curLen < jsonSize)
    {
        //数据还没有完全到达，我们还要等待一会数据到了，再解析消息体。由于标志没变，一会还是解析消息体
        parserBreak = true; //终止解析
        return true;
    }
    Json::Reader reader;    //json解析类
    if (!reader.parse((char *)(*curData), 
        (char *)((*curData) + jsonSize), mCurMsg.body, false))
    {
        return false;
    }
    //解析指针向前移动jsonSize字节
    (*curData) += jsonSize;
    curLen -= jsonSize;
    parserLen += jsonSize;
    mCurParserStatus = ON_PARSER_BODY;
    return true;
}

//从网络字节流中解析出来协议消息,len由socket函数recv返回
bool MyProtoDeCode::parser(void * data, size_t len)
{
    if (len <= 0)
    {
        return false;
    }
    uint32_t curLen = 0;//用于保存未解析的网络字节流长度（是对vector)
    uint32_t parserLen = 0;//保存vector中已经被解析完成的字节流，一会用于清除vector中数据
    uint8_t * curData = NULL;//指向data,当前未解析的网络字节流
    curData = (uint8_t *)data;
    //把当前要解析的网络字节流写入未解析完字节流之后
    while (len--)
    {
        mCurReserved.push_back(*curData);
        ++curData;
    }
    curLen = mCurReserved.size();
    curData = (uint8_t *)&mCurReserved[0];
    //只要还有未解析的网络字节流，就持续解析
    while (curLen > 0)
    {
        bool parserBreak = false;
        //解析协议头
        //注意：标识很有用，当数据没有完全达到，会等待下一次接受数据以后继续解析头部
        if (ON_PARSER_INIT == mCurParserStatus ||
            ON_PARSER_BODY == mCurParserStatus)
        {
            if (!parserHead(&curData, curLen, parserLen, parserBreak))
            {
                return false;
            }
            //退出循环，等待下一次数据到达，一起解析头部
            if (parserBreak) break;
        }
        //解析完协议头，解析协议体
        if (ON_PARSER_HAED == mCurParserStatus)
        {
            if (!parserBody(&curData, curLen, parserLen, parserBreak))
            {
                return false;
            }
            if (parserBreak) break;
        }
        if (ON_PARSER_BODY == mCurParserStatus)
        {
            //拷贝解析完的消息体放入队列中
            MyProtoMsg * pMsg = NULL;
            pMsg = new MyProtoMsg;
            *pMsg = mCurMsg;
            mMsgQ.push(pMsg);
        }
    }
    if (parserLen > 0)
    {
        //删除已经被解析的网络字节流
        mCurReserved.erase(mCurReserved.begin(), mCurReserved.begin() + parserLen);
    }
    return true;
}

bool MyProtoDeCode::empty()
{
    return mMsgQ.empty();
}

MyProtoMsg * MyProtoDeCode::front()
{
    MyProtoMsg * pMsg = NULL;
    pMsg = mMsgQ.front();
    return pMsg;
}

void MyProtoDeCode::pop()
{
    mMsgQ.pop();
}


int main()
{
    uint32_t len = 0;
    uint8_t * pData = NULL;
    MyProtoMsg msg1;
    MyProtoMsg msg2;
    MyProtoDeCode myDecode;
    MyProtoEnCode myEncode;
    //*pData = pMsg->head.VER;
    //msg1.head.VER = 1;//设置版本号
    msg1.head.MID = 12345; // 设置任务标志
    msg1.head.SID = 987654321; // 设置信源
    msg1.head.DID = 123456789; // 设置信宿
    msg1.head.BID = 987654321; // 设置信息分类标志
    msg1.head.No = 1; // 设置包序号
    msg1.head.FLAG = 0; // 设置信息处理标志
    msg1.head.Backup = 0; // 设置备用字段
    msg1.head.DATE = 1229; // 设置发送日期
    msg1.head.TIME = 123456; // 设置发送时间

    msg1.body["op"] = "set";
    msg1.body["key"] = "id";
    msg1.body["value"] = "9856";

    //msg2.head.VER = 1;//设置版本号
    msg2.head.MID = 54321; // 设置任务标志
    msg2.head.SID = 123456789; // 设置信源
    msg2.head.DID = 987654321; // 设置信宿
    msg2.head.BID = 123456789; // 设置信息分类标志
    msg2.head.No = 2; // 设置包序号
    msg2.head.FLAG = 1; // 设置信息处理标志
    msg2.head.Backup = 0; // 设置备用字段
    msg2.head.DATE = 1229; // 设置发送日期
    msg2.head.TIME = 654321; // 设置发送时间

    msg2.body["op"] = "get";
    msg2.body["key"] = "id";

    myDecode.init();
    pData = myEncode.encode(&msg1, len);
    if (!myDecode.parser(pData, len))
    {
        cout << "parser falied!" << endl;
    }
    else
    {
        cout << "msg1 parser successful!" << endl;
    }
    pData = myEncode.encode(&msg2, len);
    if (!myDecode.parser(pData, len))
    {
        cout << "parser falied!" << endl;
    }
    else
    {
        cout << "msg2 parser successful!" << endl;
    }
    MyProtoMsg * pMsg = NULL;
    while (!myDecode.empty())
    {
        pMsg = myDecode.front();
        myProtoMsgPrint(*pMsg);
        myDecode.pop();
    }
    return 0;
}
