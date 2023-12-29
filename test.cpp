#include <iostream>
#include <sstream>
#include <vector>
#include "players.hpp"

auto main() -> int {
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

    me.hit({2, 1});
    std::cout << me << std::endl;
    me.hit({4, 1});
    std::cout << me << std::endl;
    me.hit({3, 1});
    std::cout << me << std::endl;
    me.hit({5, 4});
    std::cout << me << std::endl;
    me.hit({5, 3});
    std::cout << me << std::endl;
}