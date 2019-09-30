// ® Copyright FURGBot 2019


#ifndef SYSTEM_H
#define SYSTEM_H


#include "geometry/point_2d.h"
#include "io/serial_message.h"
#include "io/serial_sender.h"
#include "system/ball.h"
#include "system/robot.h"

#include "json.hpp"

#include <cinttypes>
#include <chrono>
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
        std::vector<geometry::Point2D> goals_;

        //Serial Networking
        int serial_package_id_;
        std::chrono::duration<float> serial_sending_frequency_;
        std::string serial_port_name_;
        int frequency_;
        float period_;
        int max_sending_queue_size_;
        io::SerialSender *serial_sender_;
        io::SerialMessage serial_message_;

    public:
        System();
        ~System();

        void init();
        void setConfigurations();
        void setDefaults();

        void printConfigurations();
        void printDefaults();

        //Getters
        Ball getBall();
        std::vector<Robot> getRobots(int which);
        int getSerialPackageId();
        std::chrono::duration<float> getSerialSendingFrequency();
        io::SerialSender* getSerialSender();
        io::SerialMessage getSerialMessage();

        //Setters
        void setBall(Ball ball);
        void setRobots(int which, std::vector<Robot> robots);
        void setSerialSender(std::string serial_port_name);
        void setSerialSendingFrequency(int frequency);
};

}
}


#endif // SYSTEM_H