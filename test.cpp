#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include "players.hpp"

auto main() -> int {
    std::fstream file("../database.txt");

    std::string name1, name2;
    int a1, b1, a2, b2;
    file >> name1 >> a1 >> b1;
    file >> name2 >> a2 >> b2;

    std::cout << name1 << std::endl
              << a1 + b1 << std::endl;

    std::cout << name2 << std::endl
              << a2 + b2 << std::endl;

    std::map<std::string, std::pair<int, int>> memory;
    memory[name1] = {a1, b1};
    memory[name2] = {a2, b2};

    std::cout << memory[name1].first << " " << memory[name1].second << std::endl;
}