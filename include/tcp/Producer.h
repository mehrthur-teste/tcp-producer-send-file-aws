#pragma once
#include <string>

namespace tcp {

class Producer {
public:
    Producer(const std::string& host, int port);
    bool connect();
    bool sendMessage(const std::string& msg);
    void disconnect();

private:
    int socket_fd;
    std::string host;
    int port;
};

}
