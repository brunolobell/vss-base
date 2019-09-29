// ® Copyright FURGBot 2019


#include "geometry/field_section.h"


namespace vss_furgbol {
namespace geometry {

FieldSection::FieldSection() {}

FieldSection::~FieldSection() {}

int FieldSection::getMinX() { return min_x_; }

int FieldSection::getMinY() { return min_y_; }

int FieldSection::getMaxX() { return max_x_; }

int FieldSection::getMaxY() { return max_y_; }

void FieldSection::setMinX(int min_x) { min_x_ = min_x; }

void FieldSection::setMinY(int min_y) { min_y_ = min_y; }

void FieldSection::setMaxX(int max_x) { max_x_ = max_x; }

void FieldSection::setMaxY(int max_y) { max_y_ = max_y; }

void FieldSection::operator=(FieldSection field) {
    min_x_ = field.min_x_;
    min_y_ = field.min_y_;
    max_x_ = field.max_x_;
    max_y_ = field.max_y_;
}

} // geometry
} // vss_furgbol