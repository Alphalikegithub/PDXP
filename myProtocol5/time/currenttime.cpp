#include <iostream>
#include <chrono>

int main() {
    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();
    // 将时间戳转换为秒数
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    std::cout << "当前时间戳: " << timestamp << " 秒" << std::endl;

    return 0;

    //g++ -std=c++11 current_timestamp.cpp -o current_timestamp

}
