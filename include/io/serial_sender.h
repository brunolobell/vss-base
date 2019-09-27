// Copyright FURGBot 2019

#ifndef SERIAL_SENDER_H
#define SERIAL_SENDER_H


#include "io/serial_message.h"

#include <boost/asio.hpp>


namespace vss_furgbol {
namespace io {

class SerialSender {
    private:
        boost::asio::streambuf buf_;
        boost::asio::io_service io_service_;
        boost::asio::streambuf::const_buffers_type buffer_;
        boost::asio::serial_port serial_port_;

    public:
        SerialSender(std::string serial_port_name);
        ~SerialSender();

        void send(std::vector<unsigned char> buffer_to_send);
};

} // namespace io
} // namespace vss_furgbol


#endif