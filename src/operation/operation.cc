// ® Copyright FURGBot 2019


#include "operation/operation.h"
#include "geometry/vector_2d.h"


namespace vss_furgbol {
namespace operation {

Operation::Operation() : max_queue_size_(10) {}

Operation::Operation(int max_queue_size, geometry::Point2D enemy_goal, geometry::Point2D friendly_goal) 
    : max_queue_size_(max_queue_size), enemy_goal_(enemy_goal), friendly_goal_(friendly_goal) {}

Operation::~Operation() {}

void Operation::setTarget() {
    switch (robot_->getRole()) {
        case system::GK:
            robot_->setTarget(geometry::Point2D(robot_->getPosition().getX(), ball_->getPosition().getY()));
            break;
        case system::CB:
            robot_->setTarget(
                geometry::Point2D(
                    robot_->getPosition().getX(),
                    geometry::Vector2D(
                        friendly_goal_,
                        ball_->getPosition()
                    ).getReferentY(robot_->getPosition().getX())
                )
            );
            break;
        case system::ST:
            robot_->setTarget(
                geometry::Point2D(
                    robot_->getPosition().getX(),
                    geometry::Vector2D(
                        ball_->getPosition(),
                        enemy_goal_
                    ).getReferentY(robot_->getPosition().getX())
                )
            );
            break;
    }
}

void Operation::setMotion() {
    geometry::Point2D robot_position_ = robot_->getPosition();
    geometry::Point2D robot_target_ = robot_->getTarget();

    float max_ball_distance = robot_->getMaxBallDistance();
    float ball_x = ball_->getPosition().getX();
    float ball_y = ball_->getPosition().getY();
    float robot_x = robot_position_.getX();
    float robot_y = robot_position_.getY();

    if ((ball_x - robot_x) > max_ball_distance) rotating_ = false;

    while ((robot_position_ != robot_target_) && (!rotating_)) {
        if ((ball_x - robot_x) <= max_ball_distance) {
            rotating_ = true;
            linear_direction_ = 0;
            linear_direction_ = POSITIVE;
            angular_velocity_ = robot_->getMaxVelocity();
            if (ball_y < robot_y) angular_direction_ = NEGATIVE;
            else angular_direction_ = POSITIVE;
        }
    }
}

} // namespace operation
} // namespace vss_furgbol