#include "db.hpp"
#include <fstream>
#include <map>

Db::Db(std::string fileName) {
    _fileName = fileName;
    std::fstream file(_fileName);

    std::string name;
    std::pair<int, int> stats;

    while (file.peek() != EOF) {
        file >> name >> stats.first >> stats.second;
        _data[name] = stats;
    }
}

Db::~Db() {
    std::fstream file(_fileName);
    for (const auto& [key, value] : _data) {
        file << key << " " << value.first << " " << value.second << "\n";
    }
}

auto Db::findEntry(std::string name) -> std::pair<int, int> {
    auto it = _data.find(name);
    std::pair<int, int> res;

    if (it != _data.end()) {
        res = it->second;
    } else {
        res = {0, 0};
        _data[name] = res;
    }

    return res;
}

auto Db::updateEntry(std::string name, std::pair<int, int> stats) -> void {
    _data[name] = stats;
}
