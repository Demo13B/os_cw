#include "player.hpp"

Player::Player(std::string name, int wins, int losses, std::vector<std::pair<int, int>> positions) {
    _name = name;
    _wins = wins;
    _losses = losses;
    _remainingSquares = 20;

    _field.resize(10);

    for (size_t i = 0; i != 10; ++i) {
        for (size_t i = 0; i != 10; ++i) {
            _field[i].push_back('.');
        }
    }

    for (std::pair<int, int> pos : positions) {
        _field[pos.first][pos.second] = '1';
    }
}

auto Player::stats() -> std::pair<int, int> {
    std::pair<int, int> p{_wins, _losses};
    return p;
}

auto Player::hit(std::pair<int, int> pos) -> bool {
    if (_field[pos.first][pos.second] == '.') {
        _field[pos.first][pos.second] = '#';
        return false;
    } else {
        _field[pos.first][pos.second] = 'X';
        _remainingSquares--;
        return true;
    }
}