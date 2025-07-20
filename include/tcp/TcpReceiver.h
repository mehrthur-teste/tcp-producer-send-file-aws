#ifndef TCP_RECEIVER_H
#define TCP_RECEIVER_H

#include <string>
#include <vector>

namespace tcp {

class TcpReceiver {
private:
    int sock;
    std::string serverIp;
    int serverPort;

public:
    TcpReceiver(const std::string& ip, int port);
    ~TcpReceiver();

    bool connectToServer();
    std::vector<uint8_t> receiveBytes(size_t maxLen = 4096);
    void closeConnection();
};

} // namespace tcp

#endif
