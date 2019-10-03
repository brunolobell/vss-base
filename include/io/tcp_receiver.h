// ® Copyright FURGBot 2019


#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H


#include "system/system.h"

#include <Communications/StateReceiver.h>
#include <mutex>


namespace vss {
namespace io {

class TCPReceiver {
    private:
        vss::State state_;
        vss::IStateReceiver *state_receiver_;

        system::System *system_;

        bool *running_;
        bool *status_changed_;
        std::mutex mutex_;

        void setConfigurations();
        void printConfigurations();

        void exec();
        void end();

    public:
        TCPReceiver();
        TCPReceiver(system::System *system, bool *running, bool *status_changed);
        ~TCPReceiver();

        void init();
};

} // namespace io
} // namespace vss


#endif // TCP_RECEIVER_H