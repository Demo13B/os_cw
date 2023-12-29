#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include "db.hpp"
#include "player.hpp"

auto main() -> int {
    Db db("../database.dat");
    std::pair<int, int> p = db.findEntry("Dac");
    std::cout << p.first << " " << p.second << std::endl;
    db.updateEntry("Dac", {p.first + 1, p.second + 1});
}