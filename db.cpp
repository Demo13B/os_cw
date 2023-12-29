#include "db.hpp"
#include <fstream>
#include <map>

Db::Db(std::string fileName) {
    _file.open(fileName);
}

auto Db::extractData() -> void {
    std::string name;
    std::pair<int, int> stats;
    _file >> name >> stats.first >> stats.second;

    while (name != "") {
        _data[name] = stats;
        _file >> name >> stats.first >> stats.second;
    }
}

auto Db::putData() -> void {
    for (const auto& [key, value] : _data) {
        _file.seekp(0);
        _file << key << " " << value.first << " " << value.second << "\n";
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
