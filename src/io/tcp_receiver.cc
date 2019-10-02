// ® Copyright FURGBot 2019


#include "io/tcp_receiver.h"

#include <iostream>


namespace vss_furgbol {
namespace io {

TCPReceiver::TCPReceiver() {}

TCPReceiver::TCPReceiver(std::vector<system::Robot> friendly_robots, std::vector<system::Robot> enemy_robots, system::Ball *ball, bool *running, bool *status_changed) : 
    ball_(ball), friendly_robots_(friendly_robots), enemy_robots_(enemy_robots), running_(running), status_changed_(status_changed) {}

TCPReceiver::~TCPReceiver() {}

void TCPReceiver::init() {
    setConfigurations();
    printConfigurations();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = true;
    }

    state_receiver_ = new vss::StateReceiver();
    exec();

    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = false;
    }
    end();
    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = true;
    }
}

void TCPReceiver::exec() {
    while (*running_) state_ = state_receiver_->receiveState(vss::FieldTransformationType::None);
}

void TCPReceiver::end() { std::cout << "[STATUS]: Closing TCP..." << std::endl; }

void TCPReceiver::setConfigurations() { std::cout << "[STATUS]: Configuring TCP..." << std::endl; }

void TCPReceiver::printConfigurations() { std::cout << "[STATUS]: TCP configuration done!" << std::endl; }

} // namespace io
} // namespace vss_software