// ® Copyright FURGBot 2019


#ifndef SERIAL_MESSAGE_H
#define SERIAL_MESSAGE_H


#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>


namespace vss_furgbol {
namespace serial {

class SerialMessage {
    private:
        uint16_t pkg_id_;
        uint8_t msg_type_;
        uint8_t robot_id_;
        uint8_t velocity_linear_;
        uint8_t velocity_angular_;
        uint8_t direction_linear_;
        uint8_t direction_angular_;
        
    public:
        SerialMessage();
        ~SerialMessage();

        void serialize(std::vector<unsigned char> &buffer);

        void clear();

        void setPkgId(uint16_t pkg_id);
        void setMsgType(uint8_t msg_type);
        void setRobotId(uint8_t robot_id);
        void setVelocityLinear(uint8_t velocity_linear);
        void setVelocityAngular(uint8_t velocity_angular);
        void setDirectionLinear(uint8_t direction_linear);
        void setDirectionAngular(uint8_t direction_angular);

        uint16_t getPkgId();
        uint8_t getMsgType();
        uint8_t getRobotId();
        uint8_t getVelocityLinear();
        uint8_t getVelocityAngular();
        uint8_t getDirectionLinear();
        uint8_t getDirectionAngular();
};

}  // namespace serial
}  // namespace vss_furgbol


#endif // SERIAL_MESSAGE_H