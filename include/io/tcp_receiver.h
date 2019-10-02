// ® Copyright FURGBot 2019


#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H


#include "system/ball.h"
#include "system/robot.h"

#include <Communications/StateReceiver.h>
#include <mutex>


namespace vss_furgbol {
namespace io {

class TCPReceiver {
    private:
        vss::State state_;
        vss::IStateReceiver *state_receiver_;

        system::Ball *ball_;
        std::vector<system::Robot> friendly_robots_;
        std::vector<system::Robot> enemy_robots_;

        bool *running_;
        bool *status_changed_;
        std::mutex mutex_;

        void setConfigurations();
        void printConfigurations();

        void exec();
        void end();

    public:
        TCPReceiver();
        TCPReceiver(std::vector<system::Robot> friendly_robots, std::vector<system::Robot> enemy_robots, system::Ball *ball, bool *running, bool *status_changed);
        ~TCPReceiver();

        void init();
};

} // namespace io
} // namespace vss_furgbol


#endif // TCP_RECEIVER_H