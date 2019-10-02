// ® Copyright FURGBot 2019


#include "operation/operation.h"
#include "geometry/vector_2d.h"

#include "json.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>


namespace vss_furgbol {
namespace operation {

Operation::Operation() : sending_queue_() {}

Operation::Operation(system::Robot *robot, system::Ball *ball, bool *running, bool *status_changed) : robot_(robot), ball_(ball),
    sending_queue_(), status_changed_(status_changed), running_(running) {}

Operation::~Operation() {}

void Operation::setConfigurations() {
    std::ifstream _ifstream("config/operation.json");
    nlohmann::json json_file;
    _ifstream >> json_file;

    max_queue_size_ = json_file["max_queue_size"];
    velocity_k_ = json_file["velocity_gain"];
}

void Operation::printConfigurations() {
    std::cout << "[STATUS]: Operation configuration done!" << std::endl;

    std::cout << "-> Configurations:" << std::endl;
    std::cout << "Max queue size: " << max_queue_size_ << std::endl;
    std::cout << "Velocity gain: " << velocity_k_ << std::endl;
    std::cout << std::endl;
}

void Operation::init() {
    setConfigurations();
    printConfigurations();

    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = true;
    }

    exec();

    *status_changed_ = false;
    end();
}

void Operation::end() {
    std::cout << "[STATUS]: Closing operator..." << std::endl;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        *status_changed_ = true;
    }    
}

void Operation::exec() {
    while (*running_) {
        verifyPosition();
        setTarget();
        setMotion();
        serialize();
    }
}

void Operation::verifyPosition() {
    float robot_x = robot_->getPosition().getX();
    float line_x = robot_->getFieldLine().getX();

    if (robot_x == line_x) robot_->setOutOfPlace(NO);
    else if (robot_x > line_x) robot_->setOutOfPlace(AHEAD);
    else if (robot_x < line_x) robot_->setOutOfPlace(BEHIND);
}

void Operation::setTarget() {
    if (robot_->isOutOfPlace() == NO) {
        robot_->setTargetAngle(0);
        switch (robot_->getRole()) {
            case system::GK:
                robot_->setTargetPosition(
                    geometry::Point2D(
                        robot_->getPosition().getX(),
                        ball_->getPosition().getY()
                    )
                );
                break;
            case system::CB:
                robot_->setTargetPosition(
                    geometry::Point2D(
                        robot_->getPosition().getX(),
                        geometry::Vector2D(
                            geometry::Point2D(0, 1),
                            ball_->getPosition()
                        ).getReferentY(robot_->getPosition().getX())
                    )
                );
                break;
            case system::ST:
                robot_->setTargetPosition(
                    geometry::Point2D(
                        robot_->getPosition().getX(),
                        geometry::Vector2D(
                            ball_->getPosition(),
                            geometry::Point2D(1.5, 1)
                        ).getReferentY(robot_->getPosition().getX())
                    )
                );
                break;
        }
    } else {
        robot_->setTargetPosition(
            geometry::Point2D(
                robot_->getFieldLine().getX(),
                robot_->getPosition().getY()
            )
        );
        if (robot_->isOutOfPlace() == BEHIND) robot_->setTargetAngle(90);
        else if (robot_->isOutOfPlace() == AHEAD) robot_->setTargetAngle(-90);
    }
}

void Operation::setMotion() {
    float ball_x = ball_->getPosition().getX();
    float ball_y = ball_->getPosition().getY();
    float robot_x = robot_->getPosition().getX();
    float robot_y = robot_->getPosition().getY();
    float robot_angle = robot_->getAngle();
    float target_x = robot_->getTargetPosition().getX();
    float target_y = robot_->getTargetPosition().getY();
    float target_angle = robot_->getTargetAngle();
    float max_ball_distance = robot_->getMaxBallDistance();
    int max_velocity = robot_->getMaxVelocity();

    if (((ball_x - robot_x) > 0) && ((ball_x - robot_x) < max_ball_distance) && (abs(ball_y - robot_y) < max_ball_distance)) {
        linear_velocity_ = 0;
        angular_velocity_ = max_velocity;
        if (ball_y > robot_y) angular_direction_ = POSITIVE;
        else angular_direction_ = NEGATIVE;
    } else {
        if (robot_angle == target_angle) {
            if (target_angle != 0) {
                robot_->setTargetAngle(0);
                linear_velocity_ = 0;
                angular_velocity_ = 0;
            } else { 
                if (robot_->getPosition() != robot_->getTargetPosition()) {
                    angular_velocity_ = 0;
                    if (robot_->isOutOfPlace() == NO) {
                        linear_velocity_ = (int)(velocity_k_ * abs(robot_y - target_y));
                        if (linear_velocity_ > max_velocity) linear_velocity_ = max_velocity;
                        if (robot_y < target_y) linear_direction_ = NEGATIVE;
                        else if (robot_y > target_y) linear_direction_ = POSITIVE;
                    } else {
                        linear_velocity_ = (int)(velocity_k_ * abs(robot_x - target_x));
                        if (linear_velocity_ > max_velocity) linear_velocity_ = max_velocity;
                        if (robot_->isOutOfPlace() == BEHIND) linear_direction_ = POSITIVE;
                        else if (robot_->isOutOfPlace() == AHEAD) linear_direction_ = NEGATIVE;
                    }
                } else linear_velocity_ = 0;
            }
        } else {
            linear_velocity_ = 0;
            angular_velocity_ = velocity_k_ * abs(robot_angle - target_angle);
            if (angular_velocity_ > max_velocity) angular_velocity_ = max_velocity;
            if (robot_angle < target_angle) angular_direction_ = POSITIVE;
            if (robot_angle > target_angle) angular_direction_ = NEGATIVE;
        }
    }
}

void Operation::serialize() {
    buffer_to_send_ = std::vector<uint8_t>(5, 0);
    buffer_to_send_[ROBOT_ID] = robot_->getId() + 128;
    buffer_to_send_[LINEAR_VELOCITY] = linear_velocity_;
    buffer_to_send_[ANGULAR_VELOCITY] = angular_velocity_;
    buffer_to_send_[LINEAR_DIRECTION] = linear_direction_;
    buffer_to_send_[ANGULAR_DIRECTION] = angular_direction_;

    if (sending_queue_.size() > max_queue_size_) sending_queue_.pop();
    sending_queue_.push(buffer_to_send_);
}

std::queue<std::vector<uint8_t>> Operation::getSendingQueue() { return sending_queue_; }

} // namespace operation
} // namespace vss_furgbol