// ® Copyright FURGBot 2019


#include "operation/operation.h"
#include "geometry/vector_2d.h"

#include <cstdlib>


namespace vss_furgbol {
namespace operation {

Operation::Operation() : max_queue_size_(10), out_of_place_(false), rotating_(false), buffer_to_send_(std::vector<uint8_t>(5, 0)) {}

Operation::Operation(system::Robot *robot, system::Ball *ball, int max_queue_size, geometry::Point2D enemy_goal, geometry::Point2D friendly_goal) 
    : max_queue_size_(max_queue_size), enemy_goal_(enemy_goal), friendly_goal_(friendly_goal), out_of_place_(false), rotating_(false),
    robot_(robot), ball_(ball), buffer_to_send_(std::vector<uint8_t>(5, 0))  {}

Operation::~Operation() {}

void Operation::turnOn() { running_ = true; }

void Operation::turnOff() { running_ = false; }

void Operation::init() {
    while (running_) {
        watchPosition();
        setTarget();
        setMotion();
    }
}

void Operation::setTarget() {
    if (out_of_place_ != 0) {
        robot_->setTarget(
            geometry::Point2D(
                robot_->getFieldSecton().getMaxX(),
                robot_->getPosition().getY()
            )
        );
    } else {
        switch (robot_->getRole()) {
            case system::GK:
                robot_->setTarget(
                    geometry::Point2D(
                        robot_->getPosition().getX(),
                        ball_->getPosition().getY()
                    )
                );
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
}

} // namespace operation
} // namespace vss_furgbol