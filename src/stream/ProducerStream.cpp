extern "C" {
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
}

#include "stream/ProducerStream.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <cstring>
#include <chrono>

namespace stream {

ProducerStream::ProducerStream(const std::string& host, int port)
    : host(host), port(port), running(true) {
    senderThread = std::thread(&ProducerStream::senderLoop, this);
}

ProducerStream::~ProducerStream() {
    disconnect();
}

bool ProducerStream::connect() {
    return true; // UDP não conecta
}

bool ProducerStream::sendMessage(const std::string& msg) {
    if (msg.empty()) return false;{
        std::lock_guard<std::mutex> lock(queueMutex);
        messageQueue.emplace(nextSeqNum++, msg);
    }
    queueCond.notify_one();
    return true;
}

bool ProducerStream::sendFile(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    const size_t bufferSize = 1024;
    char* buffer = (char*)malloc(bufferSize);
    if (!buffer) return false;  // Verifica se malloc falhou

    while (file.good()) {
        file.read(buffer, bufferSize);
        std::streamsize bytesRead = file.gcount();
        if (bytesRead <= 0) break;

        std::string chunk(buffer, bytesRead);
        sendMessage(chunk);
    }

    free(buffer);  // Libera a memória alocada
    file.close();
    return true;
}

bool ProducerStream::sendBinary(const std::vector<uint8_t>& data) {
    if (data.empty()) return false;

    std::string binaryData(reinterpret_cast<const char*>(data.data()), data.size());

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        messageQueue.emplace(nextSeqNum++, binaryData);
    }
    queueCond.notify_one();
    return true;
}

bool ProducerStream::sendPacketWithAck(int udp_socket, const sockaddr_in& server, int seq_num, const std::string& data, int timeout_ms) {
    // Monta o pacote: 4 bytes para seq_num + data
    uint32_t net_seq = htonl(seq_num);
    std::string packet;
    packet.resize(4 + data.size());
    memcpy(&packet[0], &net_seq, 4);             // Header
    memcpy(&packet[4], data.data(), data.size()); // Payload

    char ack_buffer[64];
    socklen_t server_len = sizeof(server);

    for (int tries = 0; tries < 5; tries++) {
        ssize_t sent = sendto(udp_socket, packet.data(), packet.size(), 0,
                              (const sockaddr*)&server, server_len);
        if (sent < 0) {
            std::cerr << "Erro ao enviar pacote seq " << seq_num << std::endl;
            return false;
        }

        // Timeout para ACK
        fd_set readfds;
        FD_ZERO(&readfds);
        FD_SET(udp_socket, &readfds);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = timeout_ms * 1000;

        int ret = select(udp_socket + 1, &readfds, NULL, NULL, &tv);
        if (ret > 0 && FD_ISSET(udp_socket, &readfds)) {
            ssize_t recvd = recvfrom(udp_socket, ack_buffer, sizeof(ack_buffer) - 1, 0,
                                     (sockaddr*)&server, &server_len);
            if (recvd > 0) {
                ack_buffer[recvd] = 0;
                std::string ack_msg(ack_buffer);
                if (ack_msg == "ACK:" + std::to_string(seq_num)) {
                    return true;
                }
            }
        }

        std::cout << "Timeout esperando ACK para seq " << seq_num << ", reenviando...\n";
    }

    std::cerr << "Falha na transmissão do pacote seq " << seq_num << std::endl;
    return false;
}


// Função que envia pacote e espera ACK, retransmitindo até 5 vezes
// bool ProducerStream::sendPacketWithAck(int udp_socket, const sockaddr_in& server, int seq_num, const std::string& data, int timeout_ms) {
//     std::string packet = std::to_string(seq_num) + ":" + data;

//     char ack_buffer[64];
//     socklen_t server_len = sizeof(server);

//     for (int tries = 0; tries < 5; tries++) {
//         ssize_t sent = sendto(udp_socket, packet.c_str(), packet.size(), 0,
//                               (const sockaddr*)&server, server_len);
//         if (sent < 0) {
//             std::cerr << "Erro ao enviar pacote seq " << seq_num << std::endl;
//             return false;
//         }

//         // Set socket timeout para recvfrom
//         fd_set readfds;
//         FD_ZERO(&readfds);
//         FD_SET(udp_socket, &readfds);

//         struct timeval tv;
//         tv.tv_sec = 0;
//         tv.tv_usec = timeout_ms * 1000;

//         int ret = select(udp_socket + 1, &readfds, NULL, NULL, &tv);
//         if (ret > 0 && FD_ISSET(udp_socket, &readfds)) {
//             ssize_t recvd = recvfrom(udp_socket, ack_buffer, sizeof(ack_buffer) - 1, 0,
//                                      (sockaddr*)&server, &server_len);
//             if (recvd > 0) {
//                 ack_buffer[recvd] = 0;
//                 std::string ack_msg(ack_buffer);
//                 if (ack_msg == "ACK:" + std::to_string(seq_num)) {
//                     return true; // ACK correto recebido
//                 }
//             }
//         }

//         std::cout << "Timeout esperando ACK para seq " << seq_num << ", reenviando...\n";
//     }

//     std::cerr << "Falha na transmissão do pacote seq " << seq_num << std::endl;
//     return false;
// }

void ProducerStream::senderLoop() {
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_socket < 0) {
        std::cerr << "Erro ao criar socket UDP\n";
        return;
    }

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    inet_pton(AF_INET, host.c_str(), &server.sin_addr);

    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCond.wait(lock, [this]() { return !messageQueue.empty() || !running; });

        if (!running && messageQueue.empty()) break;

        auto [seq_num, data] = messageQueue.front();
        messageQueue.pop();
        lock.unlock();

        bool success = sendPacketWithAck(udp_socket, server, seq_num, data);
        if (!success) {
            std::cerr << "Erro: pacote seq " << seq_num << " não foi enviado com sucesso\n";
            // Aqui você pode implementar política de retry, abortar ou ignorar
        }
    }

    close(udp_socket);
}

void ProducerStream::disconnect() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        running = false;
    }
    queueCond.notify_all();

    if (senderThread.joinable())
        senderThread.join();
}

}
