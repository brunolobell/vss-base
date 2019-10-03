// ® Copyright FURGBot 2019


#include "system/system.h"

#include <chrono>


namespace vss {
namespace system {

System::System() {}

System::~System() {}

void System::init() {
    clearScreen();
    setDefaults();
    printDefaults();

    gk_operator_is_running_ = true;
    gk_operator_status_changed_ = false;
    gk_operator_ = new operation::Operation(&friendly_robots_[GK], &ball_, &gk_operator_is_running_, &gk_operator_status_changed_);
    std::cout << "[STATUS]: Configuring goalkeeper operator..." << std::endl;
    gk_operator_thread_ = std::thread(&operation::Operation::init, gk_operator_);
    while (!gk_operator_status_changed_);

    cb_operator_is_running_ = true;
    cb_operator_status_changed_ = false;
    cb_operator_ = new operation::Operation(&friendly_robots_[CB], &ball_, &cb_operator_is_running_, &cb_operator_status_changed_);
    std::cout << "[STATUS]: Configuring goalkeeper operator..." << std::endl;
    cb_operator_thread_ = std::thread(&operation::Operation::init, cb_operator_);
    while (!cb_operator_status_changed_);

    st_operator_is_running_ = true;
    st_operator_status_changed_ = false;
    st_operator_ = new operation::Operation(&friendly_robots_[ST], &ball_, &st_operator_is_running_, &st_operator_status_changed_);
    std::cout << "[STATUS]: Configuring goalkeeper operator..." << std::endl;
    st_operator_thread_ = std::thread(&operation::Operation::init, st_operator_);
    while (!st_operator_status_changed_);

    serial_is_running_ = true;
    serial_is_paused_ = true;
    serial_status_changed_ = false;
    serial_sender_ = new io::SerialSender(&serial_is_running_, &serial_is_paused_, &serial_status_changed_, gk_operator_->getSendingQueue(), cb_operator_->getSendingQueue(), st_operator_->getSendingQueue());
    serial_thread_ = std::thread(&io::SerialSender::init, serial_sender_);
    while (!serial_status_changed_);
    if (!serial_is_running_) serial_thread_.join();

    tcp_is_running_ = true;
    tcp_status_changed_ = false;
    tcp_receiver_ = new io::TCPReceiver(this, &tcp_is_running_, &tcp_status_changed_);
    tcp_thread_ = std::thread(&io::TCPReceiver::init, tcp_receiver_);
    while (!tcp_status_changed_);

    std::cout << std::endl << "**Press enter to continue.";
    std::getchar();
    clearScreen();

    exec();
}

void System::exec() {
    int option, count;

    do {
        std::cout << std::endl << std::endl << "\t------[MENU]------" << std::endl;
        std::cout << "[1] - Start system" << std::endl;
        std::cout << "[2] - Pause system" << std::endl;
        std::cout << "[0] - Close system" << std::endl;
        std::cout << "\t-> ";
        std::cin >> option;

        clearScreen();

        switch (option) {
            case 0:
                if (serial_is_running_) {
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_status_changed_ = false;
                    }
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_is_running_ = false;
                    }
                    while (!serial_status_changed_);
                    serial_thread_.join();
                }
                {
                    std::lock_guard<std::mutex> lock(gk_operator_mutex_);
                    gk_operator_status_changed_ = false;
                }
                {
                    std::lock_guard<std::mutex> lock(gk_operator_mutex_);
                    gk_operator_is_running_ = false;
                }
                while (!gk_operator_status_changed_);
                {
                    std::lock_guard<std::mutex> lock(cb_operator_mutex_);
                    cb_operator_status_changed_ = false;
                }
                {
                    std::lock_guard<std::mutex> lock(cb_operator_mutex_);
                    cb_operator_is_running_ = false;
                }
                while (!cb_operator_status_changed_);
                {
                    std::lock_guard<std::mutex> lock(st_operator_mutex_);
                    st_operator_status_changed_ = false;
                }
                {
                    std::lock_guard<std::mutex> lock(st_operator_mutex_);
                    st_operator_is_running_ = false;
                }
                while (!st_operator_status_changed_);
                {
                    std::lock_guard<std::mutex> lock(tcp_mutex_);
                    tcp_status_changed_ = false;
                }
                {
                    std::lock_guard<std::mutex> lock(serial_mutex_);
                    tcp_is_running_ = false;
                }
                while (!tcp_status_changed_);
                end();
                break;
            case 1:
                if (!serial_is_running_) {
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_is_running_ = true;
                    }
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_is_paused_ = false;
                    }
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_status_changed_ = false;
                    }
                    serial_thread_ = std::thread(&io::SerialSender::init, serial_sender_);
                    while (!serial_status_changed_);
                    if (!serial_is_running_) serial_thread_.join();
                } else if (serial_is_paused_) {
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_status_changed_ = false;
                    }
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_is_paused_ = false;
                    }
                    while (!serial_status_changed_);
                }
                break;
            case 2:
                if (!serial_is_paused_) {
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_status_changed_ = false;
                    }
                    {
                        std::lock_guard<std::mutex> lock(serial_mutex_);
                        serial_is_paused_ = true;
                    }
                    while (!serial_status_changed_);
                }
                break;
            default:
                std::cout << "**Please, insert a valid option!" << std::endl;
                break;
        }
    } while (option != 0);
}

void System::end() {
    std::cout << "[STATUS]: Closing system..." << std::endl;
    gk_operator_thread_.join();
    cb_operator_thread_.join();
    st_operator_thread_.join();
    tcp_thread_.join();
}

void System::setDefaults() {
    std::cout << "[STATUS]: Setting defaults..." << std::endl;
    std::ifstream _ifstream("config/defaults.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

    Robot goalkeeper, centerback, striker;
    geometry::FieldLine gk_field_line, cb_field_line, st_field_line;

    if (json_file["team_color"] == "blue") team_color_ = BLUE;
    if (json_file["team_color"] == "yellow") team_color_ = YELLOW;

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

    std::cout << "**Team color: ";
    if (team_color_ == BLUE) std::cout << "blue";
    if (team_color_ == YELLOW) std::cout << "yellow";
    std::cout << std::endl;

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

int System::getTeamColor() { return team_color_; }

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

void System::setTeamColor(int team_color) { team_color_ = team_color; }

void System::clearScreen() { std::cout << "\033[2J\033[1;1H"; }

}
}