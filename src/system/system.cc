// ® Copyright FURGBot 2019


#include "system/system.h"


namespace vss_furgbol {
namespace system {

System::System() : serial_package_id_(0), serial_sending_frequency_(1), 
                    buffer_to_send_(std::vector<uint8_t>(5, 0)) {}

System::~System() {}

void System::init() {
    setConfigurations();
    setDefaults();
}

void System::setConfigurations() {
    std::ifstream _ifstream("config/config.json");
    nlohmann::json json_file;
    _ifstream >> json_file;
    setSerialSender(json_file["networking"]["serial"]["port"]);
    setSerialSendingFrequency(json_file["networking"]["serial"]["sending_frequency"]);
}

void System::setDefaults() {
    std::ifstream _ifstream("config/defaults.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

    std::vector<Robot> friendly_robots;
    Robot goalkeeper, centerback, striker;

    goalkeeper.setRole(GK);
    goalkeeper.setId(json_file["robots"]["goalkeeper"]["id"]);
    goalkeeper.setMaxVelocity(json_file["robots"]["goalkeeper"]["max_velocity"]);
    centerback.setRole(CB);
    centerback.setId(json_file["robots"]["centerback"]["id"]);
    centerback.setMaxVelocity(json_file["robots"]["centerback"]["max_velocity"]);
    striker.setRole(ST);
    striker.setId(json_file["robots"]["striker"]["id"]);
    striker.setMaxVelocity(json_file["robots"]["striker"]["max_velocity"]);

    friendly_robots.push_back(goalkeeper);
    friendly_robots.push_back(centerback);
    friendly_robots.push_back(striker);

    setRobots(FRIENDLY, friendly_robots);
}

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