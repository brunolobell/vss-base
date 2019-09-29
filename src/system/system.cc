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
    geometry::FieldSection gk_field_section, cb_field_section, st_field_section;

    gk_field_section.setMinX(json_file["robots"]["goalkeeper"]["field_section"]["min_x"]);
    gk_field_section.setMinY(json_file["robots"]["goalkeeper"]["field_section"]["min_y"]);
    gk_field_section.setMaxX(json_file["robots"]["goalkeeper"]["field_section"]["max_x"]);
    gk_field_section.setMaxY(json_file["robots"]["goalkeeper"]["field_section"]["max_y"]);
    cb_field_section.setMinX(json_file["robots"]["centerback"]["field_section"]["min_x"]);
    cb_field_section.setMinY(json_file["robots"]["centerback"]["field_section"]["min_y"]);
    cb_field_section.setMaxX(json_file["robots"]["centerback"]["field_section"]["max_x"]);
    cb_field_section.setMaxY(json_file["robots"]["centerback"]["field_section"]["max_y"]);
    cb_field_section.setMinX(json_file["robots"]["striker"]["field_section"]["min_x"]);
    cb_field_section.setMinY(json_file["robots"]["striker"]["field_section"]["min_y"]);
    cb_field_section.setMaxX(json_file["robots"]["striker"]["field_section"]["max_x"]);
    cb_field_section.setMaxY(json_file["robots"]["striker"]["field_section"]["max_y"]);

    goalkeeper.setRole(GK);
    goalkeeper.setId(json_file["robots"]["goalkeeper"]["general_settings"]["id"]);
    goalkeeper.setMaxVelocity(json_file["robots"]["goalkeeper"]["general_settings"]["max_velocity"]);
    goalkeeper.setFieldSection(gk_field_section);
    centerback.setRole(CB);
    centerback.setId(json_file["robots"]["centerback"]["general_settings"]["id"]);
    centerback.setMaxVelocity(json_file["robots"]["centerback"]["general_settings"]["max_velocity"]);
    centerback.setFieldSection(cb_field_section);
    striker.setRole(ST);
    striker.setId(json_file["robots"]["striker"]["general_settings"]["id"]);
    striker.setMaxVelocity(json_file["robots"]["striker"]["general_settings"]["max_velocity"]);
    striker.setFieldSection(st_field_section);

    friendly_robots_ = {goalkeeper, centerback, striker};
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