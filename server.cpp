#include <semaphore.h>
#include <iostream>
#include <sstream>
#include "db.hpp"
#include "mq.hpp"
#include "player.hpp"

auto main() -> int {
    sem_t* client_sem = sem_open("client_sem", O_CREAT, 0777, 0);
    sem_t* server_sem = sem_open("server_sem", O_CREAT, 0777, 0);

    MQ mq = MQ("toserver.dat", "fromserver.dat");
    Db db = Db("/Users/timursalihov/OperatingSystems/CW/database.dat");

    std::string name;
    std::cout << "Enter your nickname: ";
    std::cin >> name;
    std::pair<int, int> stats = db.findEntry(name);

    std::vector<std::pair<int, int>> positions(20);
    std::pair<int, int> coord;
    std::cout << "Enter ship locations:\n";

    for (size_t i = 0; i != 20; ++i) {
        std::cin >> positions[i].first >> positions[i].second;
    }

    Player me(name, stats.first, stats.second, positions);
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
    std::cout << "Requesting client data...";

    std::string clientdata = mq.recieve();
    std::stringstream clientdataStream;
    clientdataStream << clientdata;
    std::string op_name;
    std::pair<int, int> op_stats;
    clientdataStream >> op_name >> op_stats.first >> op_stats.second;

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

    while (true) {
        if (myTurn) {
            std::pair<int, int> coord;
            std::cout << "============================" << std::endl;
            std::cout << "It's your turn" << std::endl;
            std::cout << "Enter hit coordinates: ";
            std::cin >> coord.first >> coord.second;
            std::cout << "============================" << std::endl;

            bool hit = client.hit(coord);

            if (hit) {
                std::cout << "You hit at " << coord.first << " " << coord.second << std::endl;
                std::cout << "Your field: " << std::endl;
                std::cout << me << std::endl;
                std::cout << "Opponent field:" << std::endl;
                client.anonymousPrint();
                std::cout << std::endl;

                std::stringstream command;
                command << coord.first << " " << coord.second;
                mq.send("Op_hit");
                mq.send(command.str());
                mq.send(client.extract_field());

                sem_post(client_sem);
                sem_wait(server_sem);

                if (client.remainingSquares() == 0) {
                    mq.send("Loss");

                    db.updateEntry(me.name(), {me.stats().first + 1, me.stats().second});
                    db.updateEntry(op_name, {op_stats.first, op_stats.second + 1});
                    db.syncData();

                    sem_post(client_sem);

                    std::cout << "=================" << std::endl;
                    std::cout << "You won!" << std::endl;
                    std::cout << "=================" << std::endl;
                    break;
                }
            } else {
                std::cout << "You miss at " << coord.first << " " << coord.second << std::endl;
                std::cout << "Your field: " << std::endl;
                std::cout << me << std::endl;
                std::cout << "Opponent field:" << std::endl;
                client.anonymousPrint();
                std::cout << std::endl;
                myTurn = false;

                std::stringstream command;
                command << coord.first << " " << coord.second;
                mq.send("Op_miss");
                mq.send(command.str());
                mq.send(client.extract_field());

                sem_post(client_sem);
                sem_wait(server_sem);
            }
        } else {
            std::cout << "============================" << std::endl;
            std::cout << "It's opponent's turn" << std::endl;
            std::cout << "============================" << std::endl;
            mq.send("Try");

            sem_post(client_sem);
            sem_wait(server_sem);

            std::string response = mq.recieve();
            std::stringstream res;
            res << response;
            std::pair<int, int> coord;
            res >> coord.first >> coord.second;

            bool hit = me.hit(coord);

            if (hit) {
                std::cout << "Opponent hit at " << coord.first << " " << coord.second << std::endl;
                std::cout << "Your field: " << std::endl;
                std::cout << me << std::endl;
                std::cout << "Opponent field:" << std::endl;
                client.anonymousPrint();
                std::cout << std::endl;

                std::stringstream command;
                command << coord.first << " " << coord.second;
                mq.send("You_hit");
                mq.send(command.str());
                mq.send(me.extract_field());

                sem_post(client_sem);
                sem_wait(server_sem);

                if (me.remainingSquares() == 0) {
                    mq.send("Win");

                    db.updateEntry(me.name(), {me.stats().first, me.stats().second + 1});
                    db.updateEntry(op_name, {op_stats.first + 1, op_stats.second});
                    db.syncData();

                    sem_post(client_sem);

                    std::cout << "=================" << std::endl;
                    std::cout << "You lost!" << std::endl;
                    std::cout << "=================" << std::endl;
                    break;
                }
            } else {
                std::cout << "Opponent miss at " << coord.first << " " << coord.second << std::endl;
                std::cout << "Your field: " << std::endl;
                std::cout << me << std::endl;
                std::cout << "Opponent field:" << std::endl;
                client.anonymousPrint();
                std::cout << std::endl;
                myTurn = true;

                std::stringstream command;
                command << coord.first << " " << coord.second;
                mq.send("You_miss");
                mq.send(command.str());
                mq.send(me.extract_field());

                sem_post(client_sem);
                sem_wait(server_sem);
            }
        }

        sem_unlink("server_sem");
        sem_unlink("client_sem");
    }
}