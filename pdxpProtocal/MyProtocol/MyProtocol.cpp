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
//������С���ƣ�10MB��
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
    Э��ͷ
 */

/* struct MyProtoHead
{
    uint8_t version;    //Э��汾��
    uint8_t magic;      //Э��ħ��
    uint16_t server;    //Э�鸴�õķ���ţ���ʶЭ��֮�ϵĲ�ͬ����
    uint32_t len;       //Э�鳤�ȣ�Э��ͷ����+�䳤jsonЭ���峤�ȣ�
}; */
struct MyProtoHead
{
    uint8_t  VER;           // �汾�ţ�1�ֽ�
    uint16_t MID;           // �����־��2�ֽ�
    uint32_t SID;           // ��Դ��4�ֽ�
    uint32_t DID;           // ���ޣ�4�ֽ�
    uint32_t BID;           // ��Ϣ�����־��4�ֽ�
    uint32_t No;            // ����ţ�4�ֽ�
    uint8_t  FLAG;          // ��Ϣ�����־��1�ֽ�
    uint32_t Backup;        // ���ã�4�ֽ�
    uint16_t DATE;          // �������ڣ�2�ֽ�
    uint32_t TIME;          // ����ʱ�䣺4�ֽ�
    /* uint16_t LEN;           // �����򳤶ȣ�2�ֽ� */
    uint16_t LEN;           // Э�鳤�ȣ�Э��ͷ����+�䳤jsonЭ���峤�ȣ�
};

/*
    Э����Ϣ��
 */
struct MyProtoMsg
{
    MyProtoHead head;   //Э��ͷ
    Json::Value body;   //Э����
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
    MyProto�����
 */
class MyProtoEnCode
{
public:
    //Э����Ϣ��������
    uint8_t * encode(MyProtoMsg * pMsg, uint32_t & len);
private:
    //Э��ͷ�������
    void headEncode(uint8_t * pData, MyProtoMsg * pMsg);
};

/* 
void MyProtoEnCode::headEncode(uint8_t * pData, MyProtoMsg * pMsg)
{
    //����Э��ͷ�汾��Ϊ1
    *pData = 1; 
    ++pData;
    //����Э��ͷħ��
    *pData = MY_PROTO_MAGIC;
    ++pData;
    //����Э�����ţ���head.server�����ֽ���ת��Ϊ�����ֽ���
    *(uint16_t *)pData = htons(pMsg->head.server);
    pData += 2;
    //����Э���ܳ��ȣ���head.len�����ֽ���ת��Ϊ�����ֽ���
    *(uint32_t *)pData = htonl(pMsg->head.len);
}
*/

void MyProtoEnCode::headEncode(uint8_t * pData, MyProtoMsg * pMsg)
{
    //*pData = pMsg->head.VER;
    //����Э��ͷ�汾��Ϊ1
    *pData = 1; 
    ++pData;
    *(uint16_t *)pData = htons(pMsg->head.MID);
    pData += 2;
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

/* 
uint8_t * MyProtoEnCode::encode(MyProtoMsg * pMsg, uint32_t & len)
{
    uint8_t * pData = NULL;
    Json::FastWriter fWriter;
    //Э��json�����л�
    string bodyStr = fWriter.write(pMsg->body);
    //����Э����Ϣ���л�����ܳ���
    len = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->head.len = len;
    //����Э����Ϣ���л���Ҫ�Ŀռ�
    pData = new uint8_t[len];
    //���Э��ͷ
    headEncode(pData, pMsg);
    //���Э����
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());
    return pData;
}
*/
/* 
uint8_t * MyProtoEnCode::encode(MyProtoMsg * pMsg, uint32_t & len)
{
    uint8_t * pData = NULL;
    Json::FastWriter fWriter;
    //Э��json�����л�
    string bodyStr = fWriter.write(pMsg->body);
    //����Э����Ϣ���л�����ܳ���
    len = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->head.LEN = (uint16_t)bodyStr.size();
    //����Э����Ϣ���л���Ҫ�Ŀռ�
    pData = new uint8_t[len];
    //���Э��ͷ
    headEncode(pData, pMsg);
    //���Э����
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());
    return pData;
}
 */

uint8_t* MyProtoEnCode::encode(MyProtoMsg* pMsg, uint32_t& len)
{
    uint8_t* pData = nullptr;
    Json::FastWriter fWriter;

    // ���л�Э����Ϊ JSON �ַ���
    string bodyStr = fWriter.write(pMsg->body);

    // ����Э����Ϣ���л�����ܳ��ȣ�����ͷ�����岿��
    len = MY_PROTO_HEAD_SIZE + static_cast<uint32_t>(bodyStr.size());

    // ������Ϣͷ���ĳ����ֶ�
    pMsg->head.LEN = static_cast<uint16_t>(len);

    // ����ռ�
    pData = new uint8_t[len];

    // ���Э��ͷ
    headEncode(pData, pMsg);

    // ���Э����
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData;
}




/*
    MyProto�����
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
    MyProtoMsg mCurMsg;                     //��ǰ�����е�Э����Ϣ��
    queue<MyProtoMsg *> mMsgQ;              //�����õ�Э����Ϣ����
    vector<uint8_t> mCurReserved;           //δ�����������ֽ���
    MyProtoParserStatus mCurParserStatus;   //��ǰ����״̬
};

void MyProtoDeCode::init()
{
    mCurParserStatus = ON_PARSER_INIT;
}

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

/* 
bool MyProtoDeCode::parserHead(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; //��ֹ����
        return true;
    }
    uint8_t * pData = *curData;
    //�����汾��
    mCurMsg.head.version = *pData;
    pData++;
    //����ħ��
    mCurMsg.head.magic = *pData;
    pData++;
    //ħ����һ�£��򷵻ؽ���ʧ��
    if (MY_PROTO_MAGIC != mCurMsg.head.magic)
    {
        return false;
    }
    //���������
    mCurMsg.head.server = ntohs(*(uint16_t*)pData);
    pData+=2;
    //����Э����Ϣ��ĳ���
    mCurMsg.head.len = ntohl(*(uint32_t*)pData);
    //�쳣������򷵻ؽ���ʧ��
    if (mCurMsg.head.len > MY_PROTO_MAX_SIZE)
    {
        return false;
    }
    //����ָ����ǰ�ƶ�MY_PROTO_HEAD_SIZE�ֽ�
    (*curData) += MY_PROTO_HEAD_SIZE;
    curLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    mCurParserStatus = ON_PARSER_HAED;
    return true;
}
 */

bool MyProtoDeCode::parserHead(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    if (curLen < MY_PROTO_HEAD_SIZE)
    {
        parserBreak = true; // ��ֹ����
        return true;
    }
    uint8_t * pData = *curData;
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
    // ����Э���峤�ȣ�������Ϣ���ȼ�ȥͷ������
    mCurMsg.head.LEN = ntohs(*(uint16_t*)(pData)); // ����Э��ͷ���Ķ����ȡ�����ֶ�
    //�쳣������򷵻ؽ���ʧ��
    if (mCurMsg.head.LEN > MY_PROTO_MAX_SIZE)
    {
        return false;
    }
    //����ָ����ǰ�ƶ�MY_PROTO_HEAD_SIZE�ֽ�
    (*curData) += MY_PROTO_HEAD_SIZE;
    curLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    mCurParserStatus = ON_PARSER_HAED;// ���ý���״̬
    return true;
}


bool MyProtoDeCode::parserBody(uint8_t ** curData, uint32_t & curLen, 
    uint32_t & parserLen, bool & parserBreak)
{
    parserBreak = false;
    uint32_t jsonSize = mCurMsg.head.LEN - MY_PROTO_HEAD_SIZE;

    if (curLen < jsonSize)
    {
        parserBreak = true; //��ֹ����
        return true;
    }
    Json::Reader reader;    //json������
    if (!reader.parse((char *)(*curData), 
        (char *)((*curData) + jsonSize), mCurMsg.body, false))
    {
        return false;
    }
    //����ָ����ǰ�ƶ�jsonSize�ֽ�
    (*curData) += jsonSize;
    curLen -= jsonSize;
    parserLen += jsonSize;
    mCurParserStatus = ON_PARSER_BODY;
    return true;
}


bool MyProtoDeCode::parser(void * data, size_t len)
{
    if (len <= 0)
    {
        return false;
    }
    uint32_t curLen = 0;
    uint32_t parserLen = 0;
    uint8_t * curData = NULL;
    curData = (uint8_t *)data;
    //�ѵ�ǰҪ�����������ֽ���д��δ�������ֽ���֮��
    while (len--)
    {
        mCurReserved.push_back(*curData);
        ++curData;
    }
    curLen = mCurReserved.size();
    curData = (uint8_t *)&mCurReserved[0];
    //ֻҪ����δ�����������ֽ������ͳ�������
    while (curLen > 0)
    {
        bool parserBreak = false;
        //����Э��ͷ
        if (ON_PARSER_INIT == mCurParserStatus ||
            ON_PARSER_BODY == mCurParserStatus)
        {
            if (!parserHead(&curData, curLen, parserLen, parserBreak))
            {
                return false;
            }
            if (parserBreak) break;
        }
        //������Э��ͷ������Э����
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
            //�������������Ϣ����������
            MyProtoMsg * pMsg = NULL;
            pMsg = new MyProtoMsg;
            *pMsg = mCurMsg;
            mMsgQ.push(pMsg);
        }
    }
    if (parserLen > 0)
    {
        //ɾ���Ѿ��������������ֽ���
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

/* 
int main()
{
    uint32_t len = 0;
    uint8_t * pData = NULL;
    MyProtoMsg msg1;
    MyProtoMsg msg2;
    MyProtoDeCode myDecode;
    MyProtoEnCode myEncode;
    msg1.head.server = 1;
    msg1.body["op"] = "set";
    msg1.body["key"] = "id";
    msg1.body["value"] = "9856";
    msg2.head.server = 2;
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
 */

int main()
{
    uint32_t len = 0;
    uint8_t * pData = NULL;
    MyProtoMsg msg1;
    MyProtoMsg msg2;
    MyProtoDeCode myDecode;
    MyProtoEnCode myEncode;
    //*pData = pMsg->head.VER;
    //msg1.head.VER = 1;//���ð汾��
    msg1.head.MID = 12345; // ���������־
    msg1.head.SID = 987654321; // ������Դ
    msg1.head.DID = 123456789; // ��������
    msg1.head.BID = 987654321; // ������Ϣ�����־
    msg1.head.No = 1; // ���ð����
    msg1.head.FLAG = 0; // ������Ϣ�����־
    msg1.head.Backup = 0; // ���ñ����ֶ�
    msg1.head.DATE = 1229; // ���÷�������
    msg1.head.TIME = 123456; // ���÷���ʱ��

    msg1.body["op"] = "set";
    msg1.body["key"] = "id";
    msg1.body["value"] = "9856";

    //msg2.head.VER = 1;//���ð汾��
    msg2.head.MID = 54321; // ���������־
    msg2.head.SID = 123456789; // ������Դ
    msg2.head.DID = 987654321; // ��������
    msg2.head.BID = 123456789; // ������Ϣ�����־
    msg2.head.No = 2; // ���ð����
    msg2.head.FLAG = 1; // ������Ϣ�����־
    msg2.head.Backup = 0; // ���ñ����ֶ�
    msg2.head.DATE = 1229; // ���÷�������
    msg2.head.TIME = 654321; // ���÷���ʱ��

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
