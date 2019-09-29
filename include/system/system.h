// ® Copyright FURGBot 2019


#ifndef SYSTEM_H
#define SYSTEM_H


#include "system/ball.h"
#include "system/robot.h"
#include "io/serial_sender.h"
#include "io/serial_message.h"

#include "json.hpp"

#include <chrono>
#include <string>
#include <fstream>


namespace vss_furgbol {
namespace system {

enum TeamLabels {
    ENEMY, FRIENDLY
};

class System {
    private:
        Ball ball_;
        std::vector<Robot> friendly_robots_;
        std::vector<Robot> enemy_robots_;

        //io::TCPReceiver tcp_receiver_;

        int serial_package_id_;
        std::chrono::duration<float> serial_sending_frequency_;
        io::SerialSender *serial_sender_;
        io::SerialMessage serial_message_;
        std::vector<uint8_t> buffer_to_send_;

    public:
        System();
        ~System();

        void init();
        void setConfigurations();
        void setDefaults();

        //Getters
        Ball getBall();
        std::vector<Robot> getRobots(int which);
        int getSerialPackageId();
        std::chrono::duration<float> getSerialSendingFrequency();
        io::SerialSender* getSerialSender();
        io::SerialMessage getSerialMessage();
        std::vector<uint8_t> getBuffer();

        //Setters
        void setBall(Ball ball);
        void setRobots(int which, std::vector<Robot> robots);
        void setSerialSender(std::string serial_port_name);
        void setSerialSendingFrequency(int frequency);
};

}
}


#endif // SYSTEM_H