#include "tcp/Producer.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace tcp {

Producer::Producer(const std::string& host, int port)
    : host(host), port(port), socket_fd(-1) {}

bool Producer::connect() {
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) return false;

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    return ::connect(socket_fd, (struct sockaddr*)&server, sizeof(server)) == 0;
}

bool Producer::sendMessage(const std::string& msg) {
    return send(socket_fd, msg.c_str(), msg.size(), 0) > 0;
}

void Producer::disconnect() {
    if (socket_fd != -1) close(socket_fd);
}

}
