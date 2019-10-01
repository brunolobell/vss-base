// ® Copyright FURGBot 2019


#include "geometry/vector_2d.h"

#include <math.h>


namespace vss_furgbol {
namespace geometry {

Vector2D::Vector2D() {}

Vector2D::Vector2D(Point2D origin, Point2D destiny) {
    origin_ = origin;
    destiny_ = destiny;
}

Vector2D::~Vector2D() {}

Point2D Vector2D::getOrigin() { return origin_; }

Point2D Vector2D::getDestiny() { return destiny_; }

float Vector2D::getComponentX() { return destiny_.getX() - origin_.getX(); }

float Vector2D::getComponentY() { return destiny_.getY() - origin_.getY(); }

float Vector2D::getReferentY(float x) { return (((x * getComponentY()) / destiny_.getX()) + origin_.getY()); }

void Vector2D::setOrigin(Point2D origin) { origin_ = origin; }

void Vector2D::setDestiny(Point2D destiny) { destiny_ = destiny; }

void Vector2D::operator=(Vector2D vector) {
    origin_ = vector.origin_;
    destiny_ = vector.destiny_;
}

}
}