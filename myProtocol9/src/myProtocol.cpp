#include "myprotocol.h"

using namespace std;

//----------------------------------公共函数----------------------------------
//打印协议数据信息
void myProtoMsgPrint(MyProtoMsg & msg)
{
    // 打印协议头部
    printf("Head[VER=%d,MID=%d,SID=%d,DID=%d,BID=%d,Number=%d,FLAG=%d,BACKUP=%d,DATE=%d,TIME=%d,LEN=%d],",
           msg.head.VER, msg.head.MID, msg.head.SID, msg.head.DID, msg.head.BID, msg.head.No,
           msg.head.FLAG, msg.head.Backup, msg.head.DATE, msg.head.TIME, msg.head.LEN);
    std::cout << endl;

    // 打印 Protocol Buffers 格式的协议体
    
    std::cout << "Body:" << std::endl;
    std::cout << "当前时刻: " << msg.body.current_time() << std::endl;
    std::cout << "设备状态: " << msg.body.device_status() << std::endl;
    std::cout << "方位角: " << msg.body.azimuth() << std::endl;
    std::cout << "俯仰角: " << msg.body.elevation() << std::endl;
    std::cout << "方位脱靶量: " << msg.body.azimuth_offset() << std::endl;
    std::cout << "俯仰脱靶量: " << msg.body.elevation_offset() << std::endl;
    std::cout << "测速值: " << msg.body.velocity() << std::endl;
    std::cout << "测距值: " << msg.body.distance() << std::endl;
    std::cout << "目标亮度: " << msg.body.brightness() << std::endl;
    
}


//----------------------------------协议头封装函数----------------------------------
//pData指向一个新的内存，需要pMsg中数据对pData进行填充
void MyProtoEncode::headEncode(uint8_t * pData, MyProtoMsg * pMsg)
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

//协议消息体封装函数：传入的pMsg里面只有部分数据，比如Json协议体，服务号，版本号，我们对消息编码后会修改长度信息，这时需要重新编码协议
//len返回长度信息，用于后面socket发送数据
uint8_t* MyProtoEncode::encode(MyProtoMsg * pMsg, uint32_t & len)
{
    uint8_t* pData = NULL;

    // Json::FastWriter fWriter;
    // // 序列化协议体为 JSON 字符串
    // string bodyStr = fWriter.write(pMsg->body);

    // 序列化 Protocol Buffers 消息体
    std::string bodyStr;
    pMsg->body.SerializeToString(&bodyStr);

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



//----------------------------------协议解析类----------------------------------
//初始化协议解析状态
void MyProtoDecode::init()
{
    mCurParserStatus = ON_PARSER_INIT;
}

//清空解析好的消息队列
void MyProtoDecode::clear()
{
    MyProtoMsg * pMsg = NULL;
    while (!mMsgQ.empty())
    {
        pMsg = mMsgQ.front();
        delete pMsg;
        mMsgQ.pop();
    }
}

//判断解析好的消息队列是否为空
bool MyProtoDecode::empty()
{
    return mMsgQ.empty();
}

//获取一个解析好的消息
MyProtoMsg * MyProtoDecode::front()
{
    MyProtoMsg * pMsg = NULL;
    pMsg = mMsgQ.front();
    return pMsg;
}

//出队一个消息
void MyProtoDecode::pop()
{
    mMsgQ.pop();
}

//从网络字节流中解析出来协议消息,len由socket函数recv返回
bool MyProtoDecode::parser(void * data, size_t len)
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

//用于解析消息头
bool MyProtoDecode::parserHead(uint8_t ** curData, uint32_t & curLen, 
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
bool MyProtoDecode::parserBody(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    //uint32_t jsonSize = mCurMsg.head.LEN - MY_PROTO_HEAD_SIZE;
    uint32_t protobufSize = mCurMsg.head.LEN - MY_PROTO_HEAD_SIZE;

    if (curLen < protobufSize)
    {
        //数据还没有完全到达，还要等待一会数据到了，再解析消息体。由于标志没变，一会还是解析消息体
        parserBreak = true; //终止解析
        return true;
    }
    // Json::Reader reader;    //json解析类
    // if (!reader.parse((char *)(*curData), 
    //     (char *)((*curData) + jsonSize), mCurMsg.body, false))
    // {
    //     return false;
    // }

    // 解析 Protocol Buffers 消息体
    if (!mCurMsg.body.ParseFromArray(*curData, protobufSize)) {
        return false;
    }

    // 更新解析指针和长度
    //解析指针向前移动jsonSize字节
    //(*curData) += jsonSize;
    *curData += protobufSize;
    //curLen -= jsonSize;
    curLen -= protobufSize;
    //parserLen += jsonSize;
    parserLen += protobufSize;
    mCurParserStatus = ON_PARSER_BODY;
    return true;
}
