#include "stream/ProducerStream.h"
#include <iostream>
#include <chrono>
#include <thread>

int main() {
    stream::ProducerStream producer("127.0.0.1", 9001);
    if (!producer.connect()) {
        std::cerr << "Falha ao conectar\n";
        return 1;
    }

    producer.sendMessage("Mensagem UDP 1");
    producer.sendMessage("Mensagem UDP 2");
    producer.sendMessage("Mensagem UDP 3");

    // Opcional: enviar arquivo em chunks
    producer.sendFile("arquivo.dat");

    // Aguarda uns segundos para garantir envio antes de desconectar
    std::this_thread::sleep_for(std::chrono::seconds(1));

    producer.disconnect();
    return 0;
}
