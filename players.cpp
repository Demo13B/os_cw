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
        _field[pos.first][pos.second] = 'O';
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
    } else if (_field[pos.first][pos.second] == 'O') {
        _remainingSquares--;
        _field[pos.first][pos.second] = 'X';

        int left_top_row = pos.first - 1;
        int left_top_column = pos.second - 1;
        if (left_top_row >= 0 && left_top_column >= 0) {
            _field[left_top_row][left_top_column] = '#';
        }

        int right_top_row = pos.first - 1;
        int right_top_column = pos.second + 1;
        if (right_top_row >= 0 && right_top_column <= 9) {
            _field[right_top_row][right_top_column] = '#';
        }

        int right_bottom_row = pos.first + 1;
        int right_bottom_column = pos.second + 1;
        if (right_bottom_row <= 9 && right_bottom_column <= 9) {
            _field[right_bottom_row][right_bottom_column] = '#';
        }

        int left_bottom_row = pos.first + 1;
        int left_bottom_column = pos.second - 1;
        if (left_bottom_row <= 9 && right_bottom_column >= 0) {
            _field[left_bottom_row][left_bottom_column] = '#';
        }

        int left_row = pos.first;
        int left_column = pos.second - 1;
        bool left = false;
        if (left_column >= 0) {
            left = true;
        }

        int up_row = pos.first - 1;
        int up_column = pos.second;
        bool up = false;
        if (up_row >= 0) {
            up = true;
        }

        int right_row = pos.first;
        int right_column = pos.second + 1;
        bool right = false;
        if (right_column <= 9) {
            right = true;
        }

        int bottom_row = pos.first + 1;
        int bottom_column = pos.second;
        bool bottom = false;
        if (bottom_row <= 9) {
            bottom = true;
        }

        std::vector<std::pair<int, int>> toFill;
        while (left_column >= 0 && _field[left_row][left_column] == 'X') {
            left_column -= 1;
        }

        if (left_column >= 0 && _field[left_row][left_column] == 'O') {
            return true;
        } else if (left_column >= 0 && _field[left_row][left_column] == '.') {
            toFill.push_back({left_row, left_column});
        }

        while (right_column <= 9 && _field[right_row][right_column] == 'X') {
            right_column += 1;
        }

        if (right_column <= 9 && _field[right_row][right_column] == 'O') {
            return true;
        } else if (right_column <= 9 && _field[right_row][right_column] == '.') {
            toFill.push_back({right_row, right_column});
        }

        while (up_row >= 0 && _field[up_row][up_column] == 'X') {
            up_row -= 1;
        }

        if (up_row >= 0 && _field[up_row][up_column] == 'O') {
            return true;
        } else if (up_row >= 0 && _field[up_row][up_column] == '.') {
            toFill.push_back({up_row, up_column});
        }

        while (bottom_row <= 9 && _field[bottom_row][bottom_column] == 'X') {
            bottom_row += 1;
        }

        if (bottom_row <= 9 && _field[bottom_row][bottom_column] == 'O') {
            return true;
        } else if (bottom_row <= 9 && _field[bottom_row][bottom_column] == '.') {
            toFill.push_back({bottom_row, bottom_column});
        }

        for (std::pair<int, int> point : toFill) {
            _field[point.first][point.second] = '#';
        }

        return true;
    }

    return false;
}

auto Player::name() -> std::string {
    return _name;
}

auto Player::remainingSquares() -> int {
    return _remainingSquares;
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
            if (_field[i][j] == 'O') {
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

auto coinflip() -> bool {
    srand(time(0));
    return rand() % 2;
}