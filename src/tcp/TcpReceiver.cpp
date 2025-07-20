#include "tcp/TcpReceiver.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace tcp {

TcpReceiver::TcpReceiver(const std::string& ip, int port)
    : serverIp(ip), serverPort(port), sock(-1) {}

TcpReceiver::~TcpReceiver() {
    closeConnection();
}

bool TcpReceiver::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Erro ao criar socket TCP\n";
        return false;
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serverPort);

    if (inet_pton(AF_INET, serverIp.c_str(), &serv_addr.sin_addr) <= 0) {
        std::cerr << "Endereço inválido TCP\n";
        return false;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Erro ao conectar ao servidor TCP\n";
        return false;
    }

    std::cout << "Conectado ao servidor TCP " << serverIp << ":" << serverPort << "\n";
    return true;
}

std::vector<uint8_t> TcpReceiver::receiveBytes(size_t maxLen) {
    std::vector<uint8_t> buffer(maxLen);
    ssize_t len = recv(sock, buffer.data(), maxLen, 0);
    if (len <= 0) {
        buffer.clear(); // Nada lido ou erro
    } else {
        buffer.resize(len);
    }
    return buffer;
}

void TcpReceiver::closeConnection() {
    if (sock != -1) {
        close(sock);
        sock = -1;
    }
}

} // namespace tcp
