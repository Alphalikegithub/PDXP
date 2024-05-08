// MessageManager.cpp
#include "MessageManager.h"
#include <chrono>

// 获取当前时间戳（秒）
long getCurrentTimestamp() {
    auto currentTime = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch()).count();
}


void MessageManager::createAndAddMessages(std::queue<MyProtoMsg>& msgQueue, int numMessages) {
    std::random_device rd;  // 随机数种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 作为随机数生成器
    /* std::mt19937: 这是一个 Mersenne Twister 伪随机数生成器类，它是一种非常高质量的伪随机数算法 */
    std::uniform_int_distribution<int> distribution(1, 1000); // 均匀分布，用于生成随机数
    std::uniform_int_distribution<int> flagDistribution(0, 1); // 用于生成随机的FLAG值
    //std::uniform_int_distribution<int> statusDistribution(0, 15); // 用于生成随机的设备状态值

    // 16种四位二进制数，以字符串形式存储
    std::vector<std::string> deviceStatusValues = {
        "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
        "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"
    };

    for (int i = 0; i < numMessages; ++i) {
        MyProtoMsg msg;

        // 随机生成消息头部字段
        msg.head.MID = distribution(gen); // 任务标志
        msg.head.SID = distribution(gen); // 信源
        msg.head.DID = distribution(gen); // 信宿
        msg.head.BID = distribution(gen); // 信息分类标志
        msg.head.No = i + 1; // 包序号，从1开始
        //msg.head.FLAG = flagDistribution(gen); // 信息处理标志 随机设置为0或1 
        /* distribution(gen)生成了一个范围在1到1000之间的随机整数,对于任何整数x，x % 2的结果只能是0或1 */
        msg.head.FLAG = distribution(gen) % 2; // 随机设置为0或1 
        msg.head.Backup = 0; // 备用字段
        msg.head.DATE = 2405; // 发送日期
        msg.head.TIME = 225859; // 发送时间

        /* 当前时间戳: 1715096190 秒
           当前年月日时分秒: 2024-05-07 23:36:30 */
        // 随机生成消息体字段
        msg.body.set_current_time(getCurrentTimestamp() + i); // 当前时刻
        /* *******************设备状态单独设置***************** */
        int randomIndex = distribution(gen) % deviceStatusValues.size(); // 生成随机索引
        std::string randomStatus = deviceStatusValues[randomIndex]; // 获取随机设备状态
        msg.body.set_device_status(randomStatus); // 直接设置设备状态为四位二进制字符串
        /* ************************************************** */
        //msg.body.set_device_status(statusDistribution(gen)); // 设备状态
        msg.body.set_azimuth(distribution(gen)); // 方位角
        msg.body.set_elevation(distribution(gen)); // 俯仰角
        msg.body.set_azimuth_offset(distribution(gen)); // 方位脱靶量
        msg.body.set_elevation_offset(distribution(gen)); // 俯仰脱靶量
        msg.body.set_velocity(distribution(gen)); // 测速值
        msg.body.set_distance(distribution(gen)); // 测距值
        msg.body.set_brightness(distribution(gen)); // 目标亮度

        // 添加消息到队列
        msgQueue.push(msg);
    }
}
