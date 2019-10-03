// ® Copyright FURGBot 2019


#ifndef SYSTEM_H
#define SYSTEM_H


#include "geometry/point_2d.h"
#include "io/serial_sender.h"
#include "io/tcp_receiver.h"
#include "operation/operation.h"

#include "Domain/Ball.h"
#include "Domain/Robot.h"
#include "json.hpp"

#include <cinttypes>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>


namespace vss {
namespace system {

enum TeamLabels {
    ENEMY, FRIENDLY
};

enum TeamColorLabels {
    BLUE, YELLOW
};

class System {
    private:
        //World Model
        Ball ball_;
        std::vector<vss::Robot> friendly_robots_;
        std::vector<Robot> enemy_robots_;
        int team_color_;

        //Serial
        io::SerialSender *serial_sender_;
        bool serial_is_running_;
        bool serial_is_paused_;
        bool serial_status_changed_;
        std::thread serial_thread_;
        std::mutex serial_mutex_;

        //TCP
        io::TCPReceiver *tcp_receiver_;
        bool tcp_is_running_;
        bool tcp_status_changed_;
        std::thread tcp_thread_;
        std::mutex tcp_mutex_;

        //Goalkeeper Operator
        operation::Operation *gk_operator_;
        bool gk_operator_is_running_;
        bool gk_operator_status_changed_;
        std::thread gk_operator_thread_;
        std::mutex gk_operator_mutex_;

        //Centerback Operator
        operation::Operation *cb_operator_;
        bool cb_operator_is_running_;
        bool cb_operator_status_changed_;
        std::thread cb_operator_thread_;
        std::mutex cb_operator_mutex_;

        //Striker Operator
        operation::Operation *st_operator_;
        bool st_operator_is_running_;
        bool st_operator_status_changed_;
        std::thread st_operator_thread_;
        std::mutex st_operator_mutex_;

        void setDefaults();
        void printDefaults();

        void exec();
        void end();

        void clearScreen();

    public:
        System();
        ~System();

        void init();

        //Getters
        Ball getBall();
        std::vector<Robot> getRobots(int which);
        int getTeamColor();

        //Setters
        void setBall(Ball ball);
        void setRobots(int which, std::vector<Robot> robots);
        void setTeamColor(int tam_color);
};

}
}


#endif // SYSTEM_H