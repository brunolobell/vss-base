// ® Copyright FURGBot 2019


#include "system/ball.h"


namespace vss {
namespace system {

Ball::Ball() {}

Ball::Ball(vss::Ball ball) {
    position_.setX(ball.x);
    position_.setY(ball.y);
}

Ball::~Ball() {}

geometry::Point2D Ball::getPosition() { return position_ ; }

void Ball::setPosition(geometry::Point2D position) { position_ = position; }

void Ball::operator=(Ball ball) { position_ = ball.position_; }

} // namespace system
} // namespace vss