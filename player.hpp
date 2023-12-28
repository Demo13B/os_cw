#pragma once
#include <iostream>
#include <string>
#include <vector>

class Player {
   private:
    int _wins, _losses;
    int _remainingSquares;
    std::string _name;
    std::vector<std::vector<char>> _field;

   public:
    Player(std::string name, int wins, int losses, std::vector<std::pair<int, int>> positions);
    ~Player() = default;

    auto stats() -> std::pair<int, int>;
    auto hit(std::pair<int, int> position) -> bool;
    friend auto operator<<(std::ostream& os, const Player& p) -> std::ostream&;
};

inline auto operator<<(std::ostream& os, const Player& p) -> std::ostream& {
    for (size_t i = 0; i != 10; ++i) {
        for (size_t j = 0; j != 10; ++j) {
            os << p._field[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}