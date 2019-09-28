// ® Copyright FURGBot 2019


#include "system/system.h"


namespace vss_furgbol {
namespace system {

System::System() : serial_package_id_(0), serial_sending_frequency_(1), 
                    buffer_to_send_(std::vector<uint8_t>(5, 0))
{
    friendly_robots_.push_back(Robot());
    friendly_robots_.push_back(Robot());
    friendly_robots_.push_back(Robot());

    enemy_robots_.push_back(Robot());
    enemy_robots_.push_back(Robot());
    enemy_robots_.push_back(Robot());
}

System::~System() {}

void System::init() {}

Ball System::getBall() { return ball_; }

std::vector<Robot> System::getRobots(int which) {
    switch (which) {
        case ENEMY: return enemy_robots_;
        case FRIENDLY: return friendly_robots_;
    }
}

int System::getSerialPackageId() { return serial_package_id_; }

std::chrono::duration<float> System::getSerialSendingFrequency() { return serial_sending_frequency_; }

io::SerialSender* System::getSerialSender() { return serial_sender_; }

io::SerialMessage System::getSerialMessage() { return serial_message_; }

std::vector<uint8_t> System::getBuffer() { return buffer_to_send_; }

void System::setBall(Ball ball) { ball_ = ball; }

void System::setRobots(int which, std::vector<Robot> robots) {
    switch (which) {
        case ENEMY:
            enemy_robots_ = robots;
            break;
        case FRIENDLY:
            friendly_robots_ = robots;
            break;
    }
}

void System::setSerialSender(std::string serial_port_name) { serial_sender_ = new io::SerialSender(serial_port_name); }

void System::setSerialSendingFrequency(int frequency) { serial_sending_frequency_ = std::chrono::duration<float>(1/((float)frequency)); }

}
}