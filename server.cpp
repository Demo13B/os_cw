#include <semaphore.h>
#include <iostream>
#include "mq.hpp"
#include "players.hpp"

auto main() -> int {
    sem_t* client_sem = sem_open("client_sem", O_CREAT, 0777, 0);
    sem_t* server_sem = sem_open("server_sem", O_CREAT, 0777, 0);

    MQ mq = MQ("toserver.dat", "fromserver.dat");

    std::string name;
    std::cout << "Enter your nickname: ";
    std::cin >> name;

    std::vector<std::pair<int, int>> positions(20);
    std::pair<int, int> coord;
    std::cout << "Enter ship locations:\n";

    for (size_t i = 0; i != 20; ++i) {
        std::cin >> positions[i].first >> positions[i].second;
    }

    Player me(name, 1, 0, positions);
    Player client;

    int option = 0;
    while (option != 3) {
        std::cout << "============================" << std::endl;
        std::cout << "Choose option:" << std::endl;
        std::cout << "1. Show stats" << std::endl;
        std::cout << "2. Show field" << std::endl;
        std::cout << "3. Start game" << std::endl;
        std::cout << "============================" << std::endl;
        std::cout << "Option: ";
        std::cin >> option;
        std::cout << "============================" << std::endl;

        std::pair<int, int> stats = me.stats();
        switch (option) {
            case 1:
                std::cout << "Name: " << me.name() << " Wins: " << stats.first << " Losses: " << stats.second << std::endl;
                break;

            case 2:
                std::cout << me << std::endl;
                break;

            case 3:
                std::cout << "Waiting for client response..." << std::endl;
                break;
        }
    }

    sem_post(client_sem);
    sem_wait(server_sem);

    std::cout << "Client connected successfully" << std::endl;
    std::cout << "Requesting client field...";
    std::string op_field = mq.recieve();
    client.update_field(op_field);
    std::cout << "Received" << std::endl;

    std::cout << "Sending server field to client...";
    mq.send(me.extract_field());
    std::cout << "Sent" << std::endl;

    sem_post(client_sem);
    sem_wait(server_sem);

    std::cout << "Flipping coin...";
    bool myTurn = coinflip();
    std::cout << "Flipped" << std::endl;

    if (myTurn) {
        mq.send("No");
        std::cout << "You go first" << std::endl;
    } else {
        mq.send("Yes");
        std::cout << "Opponent goes first" << std::endl;
    }

    sem_post(client_sem);
    sem_wait(server_sem);

    sem_unlink("server_sem");
    sem_unlink("client_sem");
}