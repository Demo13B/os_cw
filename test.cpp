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

    int hit = p.hit({0, 0});
    std::cout << p << std::endl;
    std::cout << hit << std::endl;

    hit = p.hit({0, 1});
    std::cout << p << std::endl;
    std::cout << hit << std::endl;

    hit = p.hit({5, 6});
    std::cout << p << std::endl;
    std::cout << hit << std::endl;

    hit = p.hit({5, 5});
    std::cout << p << std::endl;
    std::cout << hit << std::endl;

    hit = p.hit({3, 9});
    std::cout << p << std::endl;
    std::cout << hit << std::endl;
}