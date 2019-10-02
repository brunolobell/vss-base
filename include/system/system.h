// ® Copyright FURGBot 2019


#ifndef SYSTEM_H
#define SYSTEM_H


#include "geometry/point_2d.h"
#include "operation/operation.h"
#include "serial/serial_sender.h"
#include "system/ball.h"
#include "system/robot.h"

#include "json.hpp"

#include <cinttypes>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>


namespace vss_furgbol {
namespace system {

enum TeamLabels {
    ENEMY, FRIENDLY
};

class System {
    private:
        //World Model
        Ball ball_;
        std::vector<Robot> friendly_robots_;
        std::vector<Robot> enemy_robots_;

        //Serial
        serial::SerialSender *serial_sender_;
        bool serial_is_running_;
        bool serial_is_paused_;

        //Operation
        operation::Operation *gk_operator_;
        operation::Operation *cb_operator_;
        operation::Operation *st_operator_;

        //Perception
        //perception::Watcher watcher_;
        //perception::Dealer plotter_;

        void setDefaults();
        void printDefaults();

    public:
        System();
        ~System();

        void init();

        //Getters
        Ball getBall();
        std::vector<Robot> getRobots(int which);

        //Setters
        void setBall(Ball ball);
        void setRobots(int which, std::vector<Robot> robots);
};

}
}


#endif // SYSTEM_H