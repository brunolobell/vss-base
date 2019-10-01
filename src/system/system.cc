// ® Copyright FURGBot 2019


#include "system/system.h"


namespace vss_furgbol {
namespace system {

System::System() : serial_package_id_(0), serial_sending_frequency_(1), configured_(false) {}

System::~System() {}

void System::init() {
    setConfigurations();
    if (configured_) printConfigurations();
    setDefaults();
    printDefaults();
}

void System::setDefaults() {
    std::cout << "[STATUS]: Setting defaults..." << std::endl;
    std::ifstream _ifstream("config/defaults.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

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
    st_field_section.setMinX(json_file["robots"]["striker"]["field_section"]["min_x"]);
    st_field_section.setMinY(json_file["robots"]["striker"]["field_section"]["min_y"]);
    st_field_section.setMaxX(json_file["robots"]["striker"]["field_section"]["max_x"]);
    st_field_section.setMaxY(json_file["robots"]["striker"]["field_section"]["max_y"]);

    goalkeeper.setRole(GK);
    goalkeeper.setId(json_file["robots"]["goalkeeper"]["general_settings"]["id"]);
    goalkeeper.setMaxVelocity(json_file["robots"]["goalkeeper"]["general_settings"]["max_velocity"]);
    goalkeeper.setMaxBallDistance(json_file["robots"]["goalkeeper"]["general_settings"]["max_ball_distance"]);
    goalkeeper.setFieldSection(gk_field_section);
    centerback.setRole(CB);
    centerback.setId(json_file["robots"]["centerback"]["general_settings"]["id"]);
    centerback.setMaxVelocity(json_file["robots"]["centerback"]["general_settings"]["max_velocity"]);
    centerback.setMaxBallDistance(json_file["robots"]["centerback"]["general_settings"]["max_ball_distance"]);
    centerback.setFieldSection(cb_field_section);
    striker.setRole(ST);
    striker.setId(json_file["robots"]["striker"]["general_settings"]["id"]);
    striker.setMaxVelocity(json_file["robots"]["striker"]["general_settings"]["max_velocity"]);
    striker.setMaxBallDistance(json_file["robots"]["striker"]["general_settings"]["max_ball_distance"]);
    striker.setFieldSection(st_field_section);

    friendly_robots_ = {goalkeeper, centerback, striker};

    geometry::Point2D enemy_goal(
        json_file["goals"]["enemy"]["x_position"],
        json_file["goals"]["enemy"]["center"]
    );
    geometry::Point2D friendly_goal(
        json_file["goals"]["friendly"]["x_position"],
        json_file["goals"]["friendly"]["center"]
    );

    goals_ = {enemy_goal, friendly_goal};

    std::cout << "[STATUS]: Defaults setted!" << std::endl;
}

void System::printDefaults() {
    std::cout << "-> Defaults:" << std::endl;

    std::cout << "**Robots:" << std::endl;

    std::cout << "\t*Goalkeeper:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[GK].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[GK].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[GK].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField section:" << std::endl;
    std::cout << "\t\t\tMin x: " << friendly_robots_[GK].getFieldSecton().getMinX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[GK].getFieldSecton().getMinY() << std::endl;
    std::cout << "\t\t\tMax x: " << friendly_robots_[GK].getFieldSecton().getMaxX() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[GK].getFieldSecton().getMaxY() << std::endl;

    std::cout << "\t*Centerback:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[CB].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[CB].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[CB].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField section:" << std::endl;
    std::cout << "\t\t\tMin x: " << friendly_robots_[CB].getFieldSecton().getMinX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[CB].getFieldSecton().getMinY() << std::endl;
    std::cout << "\t\t\tMax x: " << friendly_robots_[CB].getFieldSecton().getMaxX() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[CB].getFieldSecton().getMaxY() << std::endl;

    std::cout << "\t*Striker:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[ST].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[ST].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[ST].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField section:" << std::endl;
    std::cout << "\t\t\tMin x: " << friendly_robots_[ST].getFieldSecton().getMinX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[ST].getFieldSecton().getMinY() << std::endl;
    std::cout << "\t\t\tMax x: " << friendly_robots_[ST].getFieldSecton().getMaxX() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[ST].getFieldSecton().getMaxY() << std::endl;

    std::cout << "**Goals:" << std::endl;

    std::cout << "\t*Enemy:" << std::endl;
    std::cout << "\t\tCenter: " << goals_[ENEMY].getY() << std::endl;
    std::cout << "\t\tX position: " << goals_[ENEMY].getX() << std::endl;

    std::cout << "\t*Friendly:" << std::endl;
    std::cout << "\t\tCenter: " << goals_[FRIENDLY].getY() << std::endl;
    std::cout << "\t\tX position: " << goals_[FRIENDLY].getX() << std::endl;

    std::cout << std::endl;
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