// SerialPortSender.cpp
#include "../include/SerialPortSender.h"
#include <iostream>
#include <sstream>
#include <thread>

using namespace boost::asio;
using namespace std;

SerialPortSender::SerialPortSender(const string& com_port)
    : io_(), sp_(io_, com_port) {
    // 设置串口参数
    sp_.set_option(serial_port_base::baud_rate(115200));
    sp_.set_option(serial_port_base::character_size(8));
    sp_.set_option(serial_port_base::parity(serial_port_base::parity::none));
    sp_.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    sp_.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
}

SerialPortSender::~SerialPortSender() {
    // 关闭串口
    sp_.close();
}

void SerialPortSender::send_angles(const vector<int>& angles) {
    try {
        int count = 0;
        for (int angle : angles) {
            ostringstream ss;
            ss << angle;
            string message = ss.str();
            write(sp_, buffer(message.c_str(), message.size()));
            cout << "Data sent: " << message << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            count++;
            if (count == 2) {
                count = 0;
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }
    }
    catch (boost::system::system_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}