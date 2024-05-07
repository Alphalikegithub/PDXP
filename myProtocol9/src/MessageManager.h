// MessageManager.h
#ifndef MESSAGE_MANAGER_H
#define MESSAGE_MANAGER_H

#include <queue>
#include "myprotocol.h" // 包含协议相关的头文件

class MessageManager {
public:
    MessageManager() {} // 默认构造函数

    // Function to create and add messages to the queue
    void createAndAddMessages(std::queue<MyProtoMsg>& msgQueue, int numMessages);
};

#endif // MESSAGE_MANAGER_H
