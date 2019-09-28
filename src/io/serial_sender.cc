// ® Copyright FURGBot 2019

#include "io/serial_sender.h"

namespace vss_furgbol {
namespace io {

SerialSender::SerialSender(std::string serial_port_name) : io_service_(), serial_port_(io_service_), buffer_(buf_.data()) {
    serial_port_.open(serial_port_name);

    try {
        serial_port_.set_option(boost::asio::serial_port_base::baud_rate(115200));
        serial_port_.set_option(boost::asio::serial_port_base::character_size(8));
    } catch (boost::system::system_error error) {
        std::cout << "Comunicator Error: " << error.what() << std::endl;
    }
}

SerialSender::~SerialSender() {
    serial_port_.close();
}

void SerialSender::send(std::vector<unsigned char> buffer_to_send) {
    serial_port_.write_some(boost::asio::buffer(buffer_to_send, buffer_to_send.size()));
}

} // namespace io
} // namespace vss_furgbol