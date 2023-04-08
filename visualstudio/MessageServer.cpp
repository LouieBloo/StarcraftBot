#include "MessageServer.h"

using json = nlohmann::json;

MessageServer::MessageServer(boost::asio::io_service& io_service) : _socket(io_service)
{
    try {
        tcp::resolver resolver(io_service);
        boost::asio::connect(_socket, resolver.resolve("localhost", "8000"));
        std::cout << "Server connected: " << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception in Message Server: " << e.what() << std::endl;
    }
}

std::string MessageServer::send_message(const json& message) {
    std::cout << "SENDING MESSAGE " << std::endl;
    try {
        // Send the message
        boost::asio::write(_socket, boost::asio::buffer(message.dump()));

        // Read the reply
        boost::asio::streambuf reply_buffer;
        boost::asio::read_until(_socket, reply_buffer, "\n");

        // Convert the reply to a string
        std::istream reply_stream(&reply_buffer);
        std::string reply;
        std::getline(reply_stream, reply);

        std::cout << "Message sent: " << message << std::endl;
        std::cout << "Reply received: " << reply << std::endl;

        return reply;
    }
    catch (std::exception& e) {
        std::cerr << "Exception in Message SEND: " << e.what() << std::endl;
    }

    return "ok";
}