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

} // namespace operation
} // namespace vss_furgbol