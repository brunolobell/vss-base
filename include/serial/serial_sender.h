// ® Copyright FURGBot 2019

#ifndef SERIAL_SENDER_H
#define SERIAL_SENDER_H


#include <boost/asio.hpp>
#include <chrono>
#include <queue>


namespace vss_furgbol {
namespace serial {

class SerialSender {
    private:
        boost::asio::streambuf buf_;
        boost::asio::io_service io_service_;
        boost::asio::streambuf::const_buffers_type buffer_;
        boost::asio::serial_port port_;

        std::string port_name_;
        int frequency_;
        float period_;
        std::chrono::duration<float> sending_frequency_;

        std::queue<std::vector<uint8_t>> *gk_sending_queue_;
        std::queue<std::vector<uint8_t>> *cb_sending_queue_;
        std::queue<std::vector<uint8_t>> *st_sending_queue_;
        int which_queue_;

        bool *paused_;
        bool *running_;

    public:
        SerialSender(bool *running);
        ~SerialSender();

        void setConfigurations();
        void printConfigurations();
        void init();
        void exec();
        void end();

        void send(int which_queue);

        //Getters
        std::string getPortName();
        int getPackageId();
        int getFrequency();
        float getPeriod();
};

} // namespace serial
} // namespace vss_furgbol


#endif