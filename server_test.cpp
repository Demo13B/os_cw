#include <semaphore.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include "mq.hpp"

auto main() -> int {
    sem_t* client_sem = sem_open("client_sem", O_CREAT, 0777, 0);
    sem_t* server_sem = sem_open("server_sem", O_CREAT, 0777, 0);

    MQ a = MQ("toserver.dat", "fromserver.dat");

    std::string command;
    std::cin >> command;

    a.send(command);
    sem_post(client_sem);
    sem_wait(server_sem);
    std::string res = a.recieve();
    while (command != "disconnect") {
        std::cout << res << "\n";
        std::cin >> command;
        a.send(command);
        sem_post(client_sem);
        sem_wait(server_sem);
        res = a.recieve();
    }
    sem_post(client_sem);

    sem_unlink("server_sem");
    sem_unlink("client_sem");
    return 0;
}