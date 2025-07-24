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
    serv_addr.sin_addr.s_addr = INADDR_ANY; // Escuta em todas as interfaces

    if (bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Erro ao fazer bind");
        return false;
    }

    if (listen(sock, 1) < 0) {
        perror("Erro ao fazer listen");
        return false;
    }

    std::cout << "Servidor TCP escutando em " << serverPort << "\n";

    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);
    int clientSock = accept(sock, (struct sockaddr*)&client_addr, &client_len);
    if (clientSock < 0) {
        perror("Erro ao aceitar conexão");
        return false;
    }

    std::cout << "Cliente conectado!\n";
    client_socket = clientSock; // novo membro da classe para o socket do cliente

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
