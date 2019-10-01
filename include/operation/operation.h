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

enum OutOfPlaceLabel {
    NO, BEHIND, AHEAD
};

class Operation {
    private:
        system::Robot *robot_;
        system::Ball *ball_;

        bool running_;

        int max_queue_size_;
        std::vector<uint8_t> buffer_to_send_;
        std::queue<std::vector<uint8_t>> sending_queue_;
         
    public:
        Operation();
        Operation(system::Robot *robot, system::Ball *ball, int max_queue_size, geometry::Point2D enemy_goal, geometry::Point2D friendly_goal);
        ~Operation();

        void turnOn();
        void turnOff();
        void init();

        void setTarget();
        void setMotion();
        void watchPosition();
        void getBack();

        void mountBuffer();
};

} // namespace operation
} // namespace vss_furgbol


#endif // OPERATION_H