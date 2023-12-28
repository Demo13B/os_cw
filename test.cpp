#include <iostream>
#include <sstream>
#include <vector>
#include "players.hpp"

auto main() -> int {
    std::vector<std::pair<int, int>> v({{0, 0}, {0, 1}, {5, 5}, {5, 6}});
    Player p("Tim", 1, 0, v);
    std::cout << p << std::endl;
    p.anonymousPrint();
    std::cout << std::endl;

    p.hit({0, 0});
    std::cout << p << std::endl;
    p.hit({0, 1});
    std::cout << p << std::endl;
}