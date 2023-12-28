cmake_minimum_required(VERSION 3.10)
project(Battleship_game)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(server_test server_test.cpp mq.cpp)
add_executable(client_test client_test.cpp mq.cpp)
add_executable(test test.cpp players.cpp)