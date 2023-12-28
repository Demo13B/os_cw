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
    auto name() -> std::string;
    friend auto operator<<(std::ostream& os, const Player& p) -> std::ostream&;
};

class Opponent {
   private:
    std::vector<std::vector<char>> _field;

   public:
    Opponent();
    ~Opponent() = default;

    auto mark_hit(std::pair<int, int> coord) -> void;
    auto mark_miss(std::pair<int, int> coord) -> void;
    friend auto operator<<(std::ostream& os, const Opponent& op) -> std::ostream&;
};
