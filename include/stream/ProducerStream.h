#pragma once
#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <Kernel/netinet/in.h>

namespace stream {

class ProducerStream {
public:
    ProducerStream(const std::string& host, int port);
    ~ProducerStream();

    bool connect();
    bool sendFile(const std::string& filePath);
    bool sendMessage(const std::string& msg);
    bool sendBinary(const std::vector<uint8_t>& data);
    void disconnect();

private:
    void senderLoop();
    bool sendPacketWithAck(int udp_socket, const sockaddr_in& server, int seq_num, const std::string& data, int timeout_ms = 100);

    std::string host;
    int port;

    std::queue<std::pair<int, std::string>> messageQueue; // agora guarda seq_num + msg
    std::mutex queueMutex;
    std::condition_variable queueCond;
    std::thread senderThread;
    std::atomic<bool> running;

    int nextSeqNum = 0;
};

}
