// ® Copyright FURGBot 2019


#include "geometry/field_section.h"


namespace vss_furgbol {
namespace geometry {

FieldSection::FieldSection() {}

FieldSection::FieldSection(float min_x, float min_y, float max_x, float max_y) {
    min_x_ = min_x;
    min_y_ = min_y;
    max_x_ = max_x;
    max_y_ = max_y;
}

FieldSection::~FieldSection() {}

float FieldSection::getMinX() { return min_x_; }

float FieldSection::getMinY() { return min_y_; }

float FieldSection::getMaxX() { return max_x_; }

float FieldSection::getMaxY() { return max_y_; }

void FieldSection::setMinX(float min_x) { min_x_ = min_x; }

void FieldSection::setMinY(float min_y) { min_y_ = min_y; }

void FieldSection::setMaxX(float max_x) { max_x_ = max_x; }

void FieldSection::setMaxY(float max_y) { max_y_ = max_y; }

FieldSection FieldSection::operator=(FieldSection field) { return FieldSection(field.min_x_, field.min_y_, field.max_x_, field.max_y_); }

} // geometry
} // vss_furgbol