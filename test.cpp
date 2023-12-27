#include <iostream>
#include <vector>

auto main() -> int {
    std::vector<std::vector<char>> _field;

    _field.resize(10);

    for (size_t i = 0; i != 10; ++i) {
        for (size_t i = 0; i != 10; ++i) {
            std::cout << '0';
        }
        std::cout << "\n";
    }
}