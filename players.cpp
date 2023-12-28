#include "players.hpp"
#include <iostream>
#include <sstream>

Player::Player(std::string name, int wins, int losses, std::vector<std::pair<int, int>> positions) {
    _name = name;
    _wins = wins;
    _losses = losses;
    _remainingSquares = 20;

    _field.resize(10);

    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            _field[i].push_back('.');
        }
    }

    for (std::pair<int, int> pos : positions) {
        _field[pos.first][pos.second] = '1';
    }
}

Player::Player() {
    _name = "";
    _wins = 0;
    _losses = 0;
    _remainingSquares = 20;

    _field.resize(10);

    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            _field[i].push_back('.');
        }
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

auto Player::name() -> std::string {
    return _name;
}

auto operator<<(std::ostream& os, const Player& p) -> std::ostream& {
    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            os << p._field[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

auto Player::anonymousPrint() -> void {
    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            if (_field[i][j] == '1') {
                std::cout << "."
                          << " ";
            } else {
                std::cout << _field[i][j] << " ";
            }
        }
        std::cout << "\n";
    }
}

auto Player::update_field(std::string data) -> void {
    std::stringstream ss;
    ss << data;

    for (size_t i = 0; i != 100; ++i) {
        int row, column;
        char symbol;
        ss >> row >> column >> symbol;
        _field[row][column] = symbol;
    }
}

auto Player::extract_field() -> std::string {
    std::stringstream ss;

    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            ss << i << " " << j << " " << _field[i][j] << " ";
        }
    }

    return ss.str();
}