// ® Copyright FURGBot 2019


#ifndef OPERATION_H
#define OPERATION_H


#include "geometry/vector_2d.h"
#include "system/ball.h"
#include "system/robot.h"

#include <cinttypes>
#include <mutex>
#include <queue>


namespace vss_furgbol {
namespace operation {

enum DirectionsLabels {
    NEGATIVE = 1, POSITIVE = 3
};

enum OutOfPlaceLabels {
    NO, BEHIND, AHEAD
};

enum BufferLabels {
    ROBOT_ID, LINEAR_VELOCITY, ANGULAR_VELOCITY, LINEAR_DIRECTION, ANGULAR_DIRECTION
};

class Operation {
    private:
        system::Robot *robot_;
        system::Ball *ball_;

        int max_queue_size_;
        int velocity_k_;

        int linear_velocity_;
        int angular_velocity_;
        int linear_direction_;
        int angular_direction_;

        bool *running_;
        bool *status_changed_;
        std::mutex mutex_;

        std::vector<uint8_t> buffer_to_send_;
        std::queue<std::vector<uint8_t>> sending_queue_;
         
    public:
        Operation();
        Operation(system::Robot *robot, system::Ball *ball, bool *running, bool *status_changed);
        ~Operation();

        void setConfigurations();
        void printConfigurations();

        void init();
        void exec();
        void end();

        void verifyPosition();
        void setTarget();
        void setMotion();

        void serialize();

        //Getters
        std::queue<std::vector<uint8_t>> getSendingQueue();
};

} // namespace operation
} // namespace vss_furgbol


#endif // OPERATION_H