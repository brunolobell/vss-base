// ® Copyright FURGBot 2019


#include "system/ball.h"


namespace vss_furgbol {
namespace system {

Ball::Ball() {}

Ball::~Ball() {}

point_2d Ball::getPosition() { return position_ ; }

std::vector<float> Ball::getMovimentation() { return movimentation_; }

void Ball::setPosition(point_2d position) { position_ = position; }

void Ball::setMovimentation(std::vector<float> movimentation) { movimentation_ = movimentation; }

void Ball::operator=(Ball ball) {
    position_ = ball.position_;
    movimentation_ = ball.movimentation_;
}

} // namespace system
} // namespace vss_furgbol