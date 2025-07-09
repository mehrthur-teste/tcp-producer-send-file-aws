#include "tcp/Producer.h"
#include <iostream>

int main() {
    tcp::Producer producer("127.0.0.1", 9000);

    if (!producer.connect()) {
        std::cerr << "Teste falhou: não conseguiu conectar.\n";
        return 1;
    }

    std::string mensagem = "Mensagem de teste";
    if (!producer.sendMessage(mensagem)) {
        std::cerr << "Teste falhou: não conseguiu enviar mensagem.\n";
        return 1;
    }

    std::cout << "Teste passou: conectou e enviou mensagem.\n";

    producer.disconnect();
    return 0;
}
