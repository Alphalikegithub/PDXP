#include <iostream>
#include "my_message.pb.h"  // 包含你的 Protocol Buffers 文件

int main() {
    MyMessageBody message;

    // 为每个字段赋值
    message.set_current_time(12345);        // 例如：设置当前时刻为 12345
    message.set_device_status(1);           // 例如：设置设备状态为 1
    message.set_azimuth(180.5);             // 例如：设置方位角为 180.5
    message.set_elevation(90.0);            // 例如：设置俯仰角为 90.0
    message.set_azimuth_offset(-100);       // 例如：设置方位脱靶量为 -100
    message.set_elevation_offset(50);       // 例如：设置俯仰脱靶量为 50
    message.set_velocity(0.005);            // 例如：设置测速值为 0.005
    message.set_distance(1000);             // 例如：设置测距值为 1000
    message.set_brightness(25);             // 例如：设置目标亮度为 25

    // 输出消息内容
    std::cout << "current_time: " << message.current_time() << std::endl;
    std::cout << "device_status: " << message.device_status() << std::endl;
    std::cout << "azimuth: " << message.azimuth() << std::endl;
    std::cout << "elevation: " << message.elevation() << std::endl;
    std::cout << "azimuth_offset: " << message.azimuth_offset() << std::endl;
    std::cout << "elevation_offset: " << message.elevation_offset() << std::endl;
    std::cout << "velocity: " << message.velocity() << std::endl;
    std::cout << "distance: " << message.distance() << std::endl;
    std::cout << "brightness: " << message.brightness() << std::endl;

    return 0;
}
