// ® Copyright FURGBot 2019


#ifndef OPERATION_H
#define OPERATION_H


#include "geometry/vector_2d.h"
#include "system/ball.h"
#include "system/robot.h"

#include <cinttypes>
#include <queue>


namespace vss_furgbol {
namespace operation {

enum DirectionsLabel {
    NEGATIVE = 1, POSITIVE = 3
};

class Operation {
    private:
        system::Robot *robot_;
        system::Ball *ball_;

        bool translating_;
        bool rotating_;

        int linear_velocity_;
        int angular_velocity_;
        int linear_direction_;
        int angular_direction_;

        geometry::Point2D enemy_goal_;
        geometry::Point2D friendly_goal_;

        int max_queue_size_;
        std::vector<uint8_t> buffer_to_send_;
        std::queue<std::vector<uint8_t>> sending_queue_;
         
    public:
        Operation();
        Operation(int max_queue_size, geometry::Point2D enemy_goal, geometry::Point2D friendly_goal);
        ~Operation();

        void setTarget();
        void setMotion();

        void mountBuffer();
        void pushOnQueue();
};

} // namespace operation
} // namespace vss_furgbol


#endif // OPERATION_H