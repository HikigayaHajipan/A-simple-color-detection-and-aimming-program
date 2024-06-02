// SerialPortSender.h
#ifndef SERIAL_PORT_SENDER_H
#define SERIAL_PORT_SENDER_H

#include <boost/asio.hpp>
#include <vector>
#include <string>

class SerialPortSender {
public:
    SerialPortSender(const std::string& com_port);
    ~SerialPortSender();
    void send_angles(const std::vector<int>& angles);

private:
    boost::asio::io_service io_;
    boost::asio::serial_port sp_;
};

#endif // SERIAL_PORT_SENDER_H