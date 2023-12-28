#include <semaphore.h>
#include <iostream>
#include "mq.hpp"

auto main() -> int {
    sem_t* client_sem = sem_open("client_sem", O_CREAT, 0777, 0);
    sem_t* server_sem = sem_open("server_sem", O_CREAT, 0777, 0);

    MQ a = MQ("fromserver.dat", "toserver.dat");

    sem_wait(client_sem);
    std::string command = a.recieve();
    std::string message;
    while (command != "disconnect") {
        std::cout << command << " your message: ";
        std::cin >> message;
        a.send(message);
        sem_post(server_sem);
        sem_wait(client_sem);
        command = a.recieve();
    }

    a.send("disconnected");
    sem_post(server_sem);

    sem_unlink("server_sem");
    sem_unlink("client_sem");
    return 0;
}