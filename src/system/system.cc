// ® Copyright FURGBot 2019


#include "system/system.h"


namespace vss_furgbol {
namespace system {

System::System() {}

System::~System() {}

void System::init() {
    setDefaults();
    printDefaults();

    gk_operator_ = new operation::Operation(&friendly_robots_[GK], &ball_);
    cb_operator_ = new operation::Operation(&friendly_robots_[CB], &ball_);
    st_operator_ = new operation::Operation(&friendly_robots_[ST], &ball_);

    serial_is_running_ = true;
    serial_is_paused_ = false;
    serial_sender_ = new serial::SerialSender(&serial_is_running_, &serial_is_paused_, gk_operator_->getSendingQueue(), cb_operator_->getSendingQueue(), st_operator_->getSendingQueue());
    serial_sender_->init();
}

void System::setDefaults() {
    std::cout << "[STATUS]: Setting defaults..." << std::endl;
    std::ifstream _ifstream("config/defaults.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

    Robot goalkeeper, centerback, striker;
    geometry::FieldLine gk_field_line, cb_field_line, st_field_line;

    gk_field_line.setX(json_file["robots"]["goalkeeper"]["field_line"]["x"]);
    gk_field_line.setMinY(json_file["robots"]["goalkeeper"]["field_line"]["min_y"]);
    gk_field_line.setMaxY(json_file["robots"]["goalkeeper"]["field_line"]["max_y"]);
    cb_field_line.setX(json_file["robots"]["centerback"]["field_line"]["x"]);
    cb_field_line.setMinY(json_file["robots"]["centerback"]["field_line"]["min_y"]);
    cb_field_line.setMaxY(json_file["robots"]["centerback"]["field_line"]["max_y"]);
    st_field_line.setX(json_file["robots"]["striker"]["field_line"]["x"]);
    st_field_line.setMinY(json_file["robots"]["striker"]["field_line"]["min_y"]);
    st_field_line.setMaxY(json_file["robots"]["striker"]["field_line"]["max_y"]);

    goalkeeper.setRole(GK);
    goalkeeper.setId(json_file["robots"]["goalkeeper"]["general_settings"]["id"]);
    goalkeeper.setMaxVelocity(json_file["robots"]["goalkeeper"]["general_settings"]["max_velocity"]);
    goalkeeper.setMaxBallDistance(json_file["robots"]["goalkeeper"]["general_settings"]["max_ball_distance"]);
    goalkeeper.setFieldLine(gk_field_line);
    centerback.setRole(CB);
    centerback.setId(json_file["robots"]["centerback"]["general_settings"]["id"]);
    centerback.setMaxVelocity(json_file["robots"]["centerback"]["general_settings"]["max_velocity"]);
    centerback.setMaxBallDistance(json_file["robots"]["centerback"]["general_settings"]["max_ball_distance"]);
    centerback.setFieldLine(cb_field_line);
    striker.setRole(ST);
    striker.setId(json_file["robots"]["striker"]["general_settings"]["id"]);
    striker.setMaxVelocity(json_file["robots"]["striker"]["general_settings"]["max_velocity"]);
    striker.setMaxBallDistance(json_file["robots"]["striker"]["general_settings"]["max_ball_distance"]);
    striker.setFieldLine(st_field_line);

    friendly_robots_ = {goalkeeper, centerback, striker};
}

void System::printDefaults() {
    std::cout << "[STATUS]: Defaults setted!" << std::endl;

    std::cout << "-> Defaults:" << std::endl;

    std::cout << "**Robots:" << std::endl;

    std::cout << "\t*Goalkeeper:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[GK].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[GK].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[GK].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField line:" << std::endl;
    std::cout << "\t\t\tX: " << friendly_robots_[GK].getFieldLine().getX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[GK].getFieldLine().getMinY() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[GK].getFieldLine().getMaxY() << std::endl;

    std::cout << "\t*Centerback:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[CB].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[CB].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[CB].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField line:" << std::endl;
    std::cout << "\t\t\tX: " << friendly_robots_[CB].getFieldLine().getX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[CB].getFieldLine().getMinY() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[CB].getFieldLine().getMaxY() << std::endl;

    std::cout << "\t*Striker:" << std::endl;
    std::cout << "\t\tID: " << friendly_robots_[ST].getId() << std::endl;
    std::cout << "\t\tMax velocity: " << friendly_robots_[ST].getMaxVelocity() << std::endl;
    std::cout << "\t\tMax ball velocity: " << friendly_robots_[ST].getMaxBallDistance() << std::endl;
    std::cout << "\t\tField line:" << std::endl;
    std::cout << "\t\t\tX: " << friendly_robots_[ST].getFieldLine().getX() << std::endl;
    std::cout << "\t\t\tMin y: " << friendly_robots_[ST].getFieldLine().getMinY() << std::endl;
    std::cout << "\t\t\tMax y: " << friendly_robots_[ST].getFieldLine().getMaxY() << std::endl;

    std::cout << std::endl;
}

Ball System::getBall() { return ball_; }

std::vector<Robot> System::getRobots(int which) {
    switch (which) {
        case ENEMY: return enemy_robots_;
        case FRIENDLY: return friendly_robots_;
    }
}

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

}
}