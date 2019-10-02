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

        //Operation
        operation::Operation gk_operator;
        operation::Operation cb_operator;
        operation::Operation st_operator;

    public:
        System();
        ~System();

        void init();
        void setDefaults();
        void printDefaults();

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