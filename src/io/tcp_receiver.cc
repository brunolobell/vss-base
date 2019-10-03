// ® Copyright FURGBot 2019


#include "io/tcp_receiver.h"

#include <iostream>


namespace vss {
namespace io {

TCPReceiver::TCPReceiver() {}

TCPReceiver::TCPReceiver(system::System *system, bool *running, bool *status_changed) : 
    system_(system), running_(running), status_changed_(status_changed) {}

TCPReceiver::~TCPReceiver() {}

void TCPReceiver::init() {
    setConfigurations();
    printConfigurations();

    state_receiver_ = new vss::StateReceiver();

    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = true;
    }
    
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
    while (*running_) {
        state_ = state_receiver_->receiveState(vss::FieldTransformationType::None);
        system_->setBall(state_.ball);
    }
}

void TCPReceiver::end() { std::cout << "[STATUS]: Closing TCP..." << std::endl; }

void TCPReceiver::setConfigurations() { std::cout << "[STATUS]: Configuring TCP..." << std::endl; }

void TCPReceiver::printConfigurations() { std::cout << "[STATUS]: TCP configuration done!" << std::endl; }

} // namespace io
} // namespace vss_software