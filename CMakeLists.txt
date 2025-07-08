cmake_minimum_required(VERSION 3.10)
project(TCPProducer)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(tcpProducer
    src/tcp/Producer.cpp
)

add_executable(main_app app/main.cpp)
target_link_libraries(main_app tcpProducer)
