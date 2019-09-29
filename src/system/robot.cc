// ® Copyright FURGBot 2019


#include "system/robot.h"


namespace vss_furgbol {
namespace system {

Robot::Robot() {}

Robot::~Robot() {}

int Robot::getId() { return id_; }

int Robot::getRole() { return role_; }

int Robot::getMaxVelocity() { return max_velocity_; }

geometry::FieldSection Robot::getFieldSecton() { return field_section_; }

point_2d Robot::getPosition() { return position_; }

point_2d Robot::getTarget() { return target_; }

std::vector<float> Robot::getMovimentation() { return movimentation_; }

void Robot::setId(int id) { id_ = id; }

void Robot::setRole(int role) { role_ = role; }

void Robot::setMaxVelocity(int max_velocity) { max_velocity_ = max_velocity; }

void Robot::setFieldSection(geometry::FieldSection field_section) { field_section_ = field_section; }

void Robot::setPosition(point_2d position) { position_ = position; }

void Robot::setTarget(point_2d target) { target_ = target; }

void Robot::setMovimentation(std::vector<float> movimentation) { movimentation_ = movimentation; }

void Robot::operator=(Robot robot) {
    id_ = robot.id_;
    role_ = robot.role_;
    position_ = robot.position_;
    target_ = robot.target_;
    movimentation_ = robot.movimentation_;
}

} // namespace system
} // namespace vss_furgbol