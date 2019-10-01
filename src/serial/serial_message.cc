// ® Copyright FURGBot 2019

#include "serial/serial_message.h"

namespace vss_furgbol {
namespace serial {

SerialMessage::SerialMessage() { clear(); }

SerialMessage::~SerialMessage() {}

void SerialMessage::clear() {
    pkg_id_ = 0;
    msg_type_ = 0;
    robot_id_ = 0;
    velocity_linear_ = 0;
    velocity_angular_ = 0;
    direction_linear_ = 0;
    direction_angular_ = 0;
}

void SerialMessage::setPkgId(uint16_t pkg_id) { pkg_id_ = pkg_id; }

void SerialMessage::setMsgType(uint8_t msg_type) { msg_type_ = msg_type; }

void SerialMessage::setRobotId(uint8_t robot_id) { robot_id_ = robot_id; }

void SerialMessage::setVelocityLinear(uint8_t velocity_linear) { velocity_linear_ = velocity_linear; }

void SerialMessage::setVelocityAngular(uint8_t velocity_angular) { velocity_angular_ = velocity_angular; }

void SerialMessage::setDirectionLinear(uint8_t direction_linear) { direction_linear_ = direction_linear; }

void SerialMessage::setDirectionAngular(uint8_t direction_angular) { direction_angular_ = direction_angular; }

uint16_t SerialMessage::getPkgId() { return pkg_id_; }

uint8_t SerialMessage::getMsgType() { return msg_type_; }

uint8_t SerialMessage::getRobotId() { return robot_id_; }

uint8_t SerialMessage::getVelocityLinear() { return velocity_linear_; }

uint8_t SerialMessage::getVelocityAngular() { return velocity_angular_; }

uint8_t SerialMessage::getDirectionLinear() { return direction_linear_; }

uint8_t SerialMessage::getDirectionAngular() { return direction_angular_; }

} // namespace serial
} // namespace vss_furgbol