#include <iostream>
#include <vector>
#include "players.hpp"

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

    Opponent op;

    std::cout << op << "\n";

    std::pair<int, int> co{1, 1};
    op.mark_hit(co);
    std::cout << op << "\n";

    co.first = 5;
    co.second = 5;
    op.mark_miss(co);
    std::cout << op << "\n";
}