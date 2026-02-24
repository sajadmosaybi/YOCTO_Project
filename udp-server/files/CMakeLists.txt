cmake_minimum_required(VERSION 3.10)

project(udp_server C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(udp_server
    udp_server.c
)

install(TARGETS udp_server
    RUNTIME DESTINATION bin
)