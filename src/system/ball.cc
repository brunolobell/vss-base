// ® Copyright FURGBot 2019


#include "system/ball.h"


namespace vss_furgbol {
namespace system {

Ball::Ball() {}

Ball::~Ball() {}

geometry::Point2D Ball::getPosition() { return position_ ; }

void Ball::setPosition(geometry::Point2D position) { position_ = position; }

void Ball::operator=(Ball ball) { position_ = ball.position_; }

} // namespace system
} // namespace vss_furgbol