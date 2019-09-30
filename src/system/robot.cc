// ® Copyright FURGBot 2019


#include "system/robot.h"


namespace vss_furgbol {
namespace system {

Robot::Robot() {}

Robot::Robot(int id, int role, int max_velocity, geometry::FieldSection field_section, geometry::Point2D position, geometry::Point2D target, std::vector<float> movimentation) {
    id_ = id;
    role_ = role;
    max_velocity_ = max_velocity;
    field_section_ = field_section;
    position_ = position;
    target = target_;
    movimentation_ = movimentation;
}

Robot::~Robot() {}

int Robot::getId() { return id_; }

int Robot::getRole() { return role_; }

int Robot::getMaxVelocity() { return max_velocity_; }

geometry::FieldSection Robot::getFieldSecton() { return field_section_; }

geometry::Point2D Robot::getPosition() { return position_; }

geometry::Point2D Robot::getTarget() { return target_; }

std::vector<float> Robot::getMovimentation() { return movimentation_; }

void Robot::setId(int id) { id_ = id; }

void Robot::setRole(int role) { role_ = role; }

void Robot::setMaxVelocity(int max_velocity) { max_velocity_ = max_velocity; }

void Robot::setFieldSection(geometry::FieldSection field_section) { field_section_ = field_section; }

void Robot::setPosition(geometry::Point2D position) { position_ = position; }

void Robot::setTarget(geometry::Point2D target) { target_ = target; }

void Robot::setMovimentation(std::vector<float> movimentation) { movimentation_ = movimentation; }

void Robot::operator=(Robot robot) {
    id_ = robot.id_;
    role_ = robot.role_; 
    max_velocity_ = robot.max_velocity_;
    field_section_ = robot.field_section_;
    position_ = robot.position_;
    target_ = robot.target_;
    movimentation_ = robot.movimentation_;
}

} // namespace system
} // namespace vss_furgbol