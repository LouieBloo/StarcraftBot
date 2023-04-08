#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <iostream>
#include "json.hpp"

using boost::asio::ip::tcp;

class MessageServer {
public:
    MessageServer(boost::asio::io_service& io_service);
    //MessageServer();
    std::string send_message(const nlohmann::json& message);

private:
    tcp::socket _socket;
};

#endif // SERVER_H
