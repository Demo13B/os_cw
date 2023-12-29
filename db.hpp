#pragma once
#include <fstream>
#include <map>

class Db {
   private:
    std::fstream _file;
    std::map<std::string, std::pair<int, int>> _data;

   public:
    Db(std::string fileName);
    ~Db() = default;

    auto extractData() -> void;
    auto putData() -> void;
    auto findEntry(std::string name) -> std::pair<int, int>;
    auto updateEntry(std::string name, std::pair<int, int> stats) -> void;
};