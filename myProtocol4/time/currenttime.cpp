#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>

int main() {
    // 获取当前时间戳
    auto now = std::chrono::system_clock::now();
    // 将时间戳转换为秒数
    auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();

    std::cout << "当前时间戳: " << timestamp << " 秒" << std::endl;

    // 获取当前本地时间
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&time);

    // 显示当前年月日时分秒
    std::cout << "当前年月日时分秒: ";
    std::cout << (localTime->tm_year + 1900) << "-"
              << std::setw(2) << std::setfill('0') << (localTime->tm_mon + 1) << "-"
              << std::setw(2) << std::setfill('0') << localTime->tm_mday << " "
              << std::setw(2) << std::setfill('0') << localTime->tm_hour << ":"
              << std::setw(2) << std::setfill('0') << localTime->tm_min << ":"
              << std::setw(2) << std::setfill('0') << localTime->tm_sec << std::endl;

    /* auto now1 = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now1);
    char buf[100] = {0};
    if (std::strftime(buf, sizeof(buf), "%c", std::localtime(&now_c))) {
        std::cout << buf << "\n";
    } */

    return 0;

    //g++ -std=c++11 currenttime.cpp -o current_timestamp

}
