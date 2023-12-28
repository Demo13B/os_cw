cmake_minimum_required(VERSION 3.10)
project(Battleship_game)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(server server.cpp mq.cpp)
add_executable(client client.cpp mq.cpp)
add_executable(test test.cpp player.cpp)