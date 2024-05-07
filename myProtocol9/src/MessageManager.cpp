// MessageManager.cpp
#include "MessageManager.h"

void MessageManager::createAndAddMessages(std::queue<MyProtoMsg>& msgQueue) {
    // 创建第一个消息
    MyProtoMsg msg1;
    msg1.head.MID = 12345; // 设置任务标志
    msg1.head.SID = 987654321; // 设置信源
    msg1.head.DID = 123456789; // 设置信宿
    msg1.head.BID = 987654321; // 设置信息分类标志
    msg1.head.No = 1; // 设置包序号
    msg1.head.FLAG = 0; // 设置信息处理标志
    msg1.head.Backup = 0; // 设置备用字段
    msg1.head.DATE = 2405; // 设置发送日期
    msg1.head.TIME = 225859; // 设置发送时间

    // 使用 Protocol Buffers 格式直接设置消息的协议体字段
    msg1.body.set_current_time(1735227015000); // 设置当前时刻
    msg1.body.set_device_status(1); // 设置设备状态
    msg1.body.set_azimuth(45.0); // 设置方位角
    msg1.body.set_elevation(30.0); // 设置俯仰角
    msg1.body.set_azimuth_offset(100); // 设置方位脱靶量
    msg1.body.set_elevation_offset(-50); // 设置俯仰脱靶量
    msg1.body.set_velocity(0.5); // 设置测速值
    msg1.body.set_distance(1000); // 设置测距值
    msg1.body.set_brightness(5); // 设置目标亮度

    // 添加第一个消息到队列
    msgQueue.push(msg1);

    // 创建第二个消息
    MyProtoMsg msg2;
    msg2.head.MID = 54321; // 设置任务标志
    msg2.head.SID = 123456789; // 设置信源
    msg2.head.DID = 987654321; // 设置信宿
    msg2.head.BID = 123456789; // 设置信息分类标志
    msg2.head.No = 2; // 设置包序号
    msg2.head.FLAG = 1; // 设置信息处理标志
    msg2.head.Backup = 0; // 设置备用字段
    msg2.head.DATE = 2405; // 设置发送日期
    msg2.head.TIME = 235860; // 设置发送时间

    // 使用 Protocol Buffers 格式直接设置消息的协议体字段
    msg2.body.set_current_time(1715012458); // 设置当前时刻
    msg2.body.set_device_status(2); // 设置设备状态
    msg2.body.set_azimuth(90.0); // 设置方位角
    msg2.body.set_elevation(60.0); // 设置俯仰角
    msg2.body.set_azimuth_offset(200); // 设置方位脱靶量
    msg2.body.set_elevation_offset(-100); // 设置俯仰脱靶量
    msg2.body.set_velocity(1.0); // 设置测速值
    msg2.body.set_distance(2000); // 设置测距值
    msg2.body.set_brightness(8); // 设置目标亮度

    // 添加第二个消息到队列
    msgQueue.push(msg2);

    // 可以根据需要创建更多的消息并添加到队列中
}
