#include <iostream>
#include <vector>
#include "player.hpp"

auto main() -> int {
    std::vector<std::pair<int, int>> v({{1, 1}, {2, 2}});
    Player p("Tim", 1, 0, v);
    std::cout << p << std::endl;

    std::pair<int, int> coord{1, 1};
    bool cond = p.hit(coord);
    if (cond) {
        std::cout << "Hit!\n";
    } else {
        std::cout << "Miss!\n";
    }
    std::cout << p << std::endl;

    coord.first = 0;
    coord.second = 0;
    cond = p.hit(coord);
    if (cond) {
        std::cout << "Hit!\n";
    } else {
        std::cout << "Miss!\n";
    }
    std::cout << p << std::endl;
}