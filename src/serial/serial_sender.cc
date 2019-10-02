// ® Copyright FURGBot 2019

#include "serial/serial_sender.h"
#include "system/robot.h"

#include "json.hpp"

#include <fstream>
#include <iostream>

namespace vss_furgbol {
namespace serial {

SerialSender::SerialSender(bool *running) : io_service_(), port_(io_service_), buffer_(buf_.data()), running_(running),
    which_queue_(system::GK) {}

SerialSender::~SerialSender() {}

void SerialSender::init() {
    setConfigurations();

    try {
        port_.open(port_name_);
        port_.set_option(boost::asio::serial_port_base::baud_rate(115200));
        port_.set_option(boost::asio::serial_port_base::character_size(8));
    } catch (boost::system::system_error error) {
        std::cout << "[SERIAL COMMUNICATOR ERROR]: " << error.what() << std::endl << std::endl;
        *running_ = false;
    }

    if (*running_) printConfigurations();

    exec();
}

void SerialSender::exec() {
    while (1) {
        while ((*running_) && (!*paused_)) {
            send(which_queue_);
            which_queue_++;
            if (which_queue_ > system::ST) which_queue_ = system::GK;
        }

        if (!*running_) {
            end();
            break;
        }
    }
}

void SerialSender::end() { port_.close(); }

void SerialSender::setConfigurations() {
    std::cout << "[STATUS]: Configuring serial..." << std::endl;
    std::ifstream _ifstream("config/serial.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

    port_name_ = json_file["port_name"];
    frequency_ = json_file["sending_frequency"];
    period_ = 1/(float)frequency_;
}

void SerialSender::printConfigurations() {
    std::cout << "[STATUS]: Serial configuration done!" << std::endl;

    std::cout << "-> Configurations:" << std::endl;
    std::cout << "Serial port: " << port_name_ << std::endl;
    std::cout << "Serial sending frequency: " << frequency_ << "hz" << std::endl;
    std::cout << "Time between serial messages: " << period_ << "s" << std::endl;
    std::cout << std::endl;
}

void SerialSender::send(int which_queue) {
    switch (which_queue) {
        case system::GK:
            port_.write_some(boost::asio::buffer(gk_sending_queue_->front(), gk_sending_queue_->front().size()));
            gk_sending_queue_->pop();
            break;
        case system::CB:
            port_.write_some(boost::asio::buffer(cb_sending_queue_->front(), cb_sending_queue_->front().size()));
            cb_sending_queue_->pop();
            break;
        case system::ST:
            port_.write_some(boost::asio::buffer(st_sending_queue_->front(), st_sending_queue_->front().size()));
            st_sending_queue_->pop();
            break;
    }
}

std::string SerialSender::getPortName() { return port_name_; }

int SerialSender::getFrequency() { return frequency_; }

float SerialSender::getPeriod() { return period_; }

} // namespace serial
} // namespace vss_furgbol