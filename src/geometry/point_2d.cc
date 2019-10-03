// ® Copyright FURGBot 2019


#include "geometry/point_2d.h"


namespace vss {
namespace geometry {

Point2D::Point2D() {}

Point2D::Point2D(float x, float y) {
    x_ = x;
    y_ = y;
}

Point2D::~Point2D() {}

float Point2D::getX() { return x_; }

float Point2D::getY() { return y_; }

void Point2D::setX(float x) { x_ = x; }

void Point2D::setY(float y) { y_ = y; }

bool Point2D::operator!=(Point2D point) {
    if ((x_ != point.x_) || (y_ != point.y_)) return true;
    return false;
}

bool Point2D::operator==(Point2D point) {
    if ((x_ == point.x_) && (y_ == point.y_)) return true;
    return false;
}

void Point2D::operator=(Point2D point) {
    x_ = point.x_;
    y_ = point.y_;
}
    
}
}