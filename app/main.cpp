#include "tcp/Producer.h"
#include <iostream>

int main() {
    tcp::Producer producer("127.0.0.1", 9000);
    if (!producer.connect()) {
        std::cerr << "Erro ao conectar\n";
        return 1;
    }

    producer.sendMessage("Hello, servidor TCP!");
    producer.disconnect();
    return 0;
}
