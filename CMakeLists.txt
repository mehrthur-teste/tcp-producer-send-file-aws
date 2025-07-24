cmake_minimum_required(VERSION 3.10)
project(TCPProducer)

set(CMAKE_CXX_STANDARD 17)

# Inclui os headers antigos e novos
include_directories(include)

# Biblioteca TCP antiga
add_library(tcpProducer
    src/tcp/Producer.cpp
    src/tcp/TcpReceiver.cpp  
)

# Biblioteca Stream UDP nova
add_library(streamProducer
    src/stream/ProducerStream.cpp
)

# Executável principal - exemplo usando UDP Stream
add_executable(main_app app/main.cpp)
target_link_libraries(main_app streamProducer tcpProducer)  # linka as duas libs

# Teste do Producer TCP antigo
add_executable(test_producer test/ProducerTest.cpp)
target_link_libraries(test_producer tcpProducer)
