cmake_minimum_required(VERSION 3.15)
project(192050193_lab_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(server server.c)
add_executable(multiThreadServer multiThreadServer.c)
add_executable(client client.c)
add_executable(client2 client2.c)
add_executable(test test.c)