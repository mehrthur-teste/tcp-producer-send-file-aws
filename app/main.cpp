#include "stream/ProducerStream.h"
#include "tcp/TcpReceiver.h"
#include <iostream>
#include <chrono>
#include <thread>

// fazer com que haja um horquestrador de uma só porta porque isso d;á muito problema dpois

int main() {
    stream::ProducerStream producer("127.0.0.1", 9001);
    if (!producer.connect()) {
        std::cerr << "Falha ao conectar no UDP\n";
        return 1;
    }

    tcp::TcpReceiver receiver("127.0.0.1", 8000);
    if (!receiver.connectToServer()) {
        std::cerr << "Falha ao conectar no TCP\n";
        return 1;
    }

    // Thread para receber do TCP e enviar via UDP
    std::thread tcp_thread([&]() {
        while (true) {
            auto data = receiver.receiveBytes();
            if (!data.empty()) {
                std::cout << "Recebido " << data.size() << " bytes do TCP\n";
                producer.sendBinary(data);
            } else {
                std::cout << "Conexão TCP encerrada ou sem dados\n";
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    // Thread principal pode fazer discovery, status, heartbeat, etc.
    while (true) {
        std::cout << "Thread principal viva (descoberta, logs...)\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    tcp_thread.join();
    producer.disconnect();
    return 0;
}
