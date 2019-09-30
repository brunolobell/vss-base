// ® Copyright FURGBot 2019


#include "system/ball.h"


namespace vss_furgbol {
namespace system {

Ball::Ball() {}

Ball::Ball(geometry::Point2D position, std::vector<float> movimentation) {
    position_ = position;
    movimentation_ = movimentation;
}

Ball::~Ball() {}

geometry::Point2D Ball::getPosition() { return position_ ; }

std::vector<float> Ball::getMovimentation() { return movimentation_; }

void Ball::setPosition(geometry::Point2D position) { position_ = position; }

void Ball::setMovimentation(std::vector<float> movimentation) { movimentation_ = movimentation; }

void Ball::operator=(Ball ball) {
    position_ = ball.position_;
    movimentation_ = ball.movimentation_;
}

} // namespace system
} // namespace vss_furgbol