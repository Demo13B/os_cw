#pragma once
#include <map>
#include <string>

class Db {
   private:
    std::string _fileName;
    std::map<std::string, std::pair<int, int>> _data;

   public:
    Db(std::string fileName);
    ~Db();

    auto findEntry(std::string name) -> std::pair<int, int>;
    auto updateEntry(std::string name, std::pair<int, int> stats) -> void;
};