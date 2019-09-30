// ® Copyright FURGBot 2019


#include "geometry/geometry.h"

#include <math.h>


namespace vss_furgbol {
namespace geometry {

float getDistanceBetweenTwoPoints(Point2D first_point, Point2D second_point) {
    Point2D point(second_point.getX() - first_point.getX(), second_point.getY() - first_point.getY());
    return sqrt((point.getX() * point.getX()) + (point.getY() * point.getY()));
}

} // namespace geometry
} // namespace vss_furgbol