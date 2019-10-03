// ® Copyright FURGBot 2019


#include "system/robot.h"


namespace vss {
namespace system {

Robot::Robot() {}

Robot::Robot(vss::Robot robot) {
    position_.setX(robot.x);
    position_.setY(robot.y);
    angle_ = robot.angle;
}

Robot::~Robot() {}

int Robot::getId() { return id_; }

int Robot::getRole() { return role_; }

int Robot::getMaxVelocity() { return max_velocity_; }

float Robot::getMaxBallDistance() { return max_ball_distance_; }

float Robot::getAngle() { return angle_; }

float Robot::getTargetAngle() { return target_angle_; }

geometry::FieldLine Robot::getFieldLine() { return field_line_; }

geometry::Point2D Robot::getPosition() { return position_; }

geometry::Point2D Robot::getTargetPosition() { return target_position_; }

int Robot::isOutOfPlace() { return out_of_place_; }

void Robot::setId(int id) { id_ = id; }

void Robot::setRole(int role) { role_ = role; }

void Robot::setMaxVelocity(int max_velocity) { max_velocity_ = max_velocity; }

void Robot::setMaxBallDistance(float max_ball_distance) { max_ball_distance_ = max_ball_distance; }

void Robot::setAngle(float angle) { angle_ = angle; }

void Robot::setTargetAngle(float target_angle) { target_angle_ = target_angle; }

void Robot::setFieldLine(geometry::FieldLine field_line) { field_line_ = field_line; }

void Robot::setPosition(geometry::Point2D position) { position_ = position; }

void Robot::setTargetPosition(geometry::Point2D target_position) { target_position_ = target_position; }

void Robot::setOutOfPlace(int out_of_place) { out_of_place_ = out_of_place; }

void Robot::operator=(Robot robot) {
    id_ = robot.id_;
    role_ = robot.role_; 
    max_velocity_ = robot.max_velocity_;
    max_ball_distance_ = robot.max_ball_distance_;
    angle_ = robot.angle_;
    target_angle_ = robot.target_angle_;
    field_line_ = robot.field_line_;
    position_ = robot.position_;
    target_position_ = robot.target_position_;
    out_of_place_ = robot.out_of_place_;
}

void Robot::operator=(vss::Robot robot) {
    position_.setX(robot.x);
    position_.setY(robot.y);
    angle_ = robot.angle;
}

} // namespace system
} // namespace vss