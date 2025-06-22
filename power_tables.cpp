#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    const int max = 10;
    std::cout << "Tablas de potencia (1..10)" << std::endl;
    std::cout << std::setw(12) << "";
    for (int exp = 1; exp <= max; ++exp) {
        std::cout << std::setw(12) << exp;
    }
    std::cout << std::endl;

    for (int base = 1; base <= 5; ++base) {
        std::cout << std::setw(12) << base;
        for (int exp = 1; exp <= max; ++exp) {
            std::cout << std::setw(12) << static_cast<unsigned long long>(std::pow(base, exp) + 0.5);
        }
        std::cout << std::endl;
    }

    std::cout << std::endl; // separator

    for (int base = 6; base <= max; ++base) {
        std::cout << std::setw(12) << base;
        for (int exp = 1; exp <= max; ++exp) {
            std::cout << std::setw(12) << static_cast<unsigned long long>(std::pow(base, exp) + 0.5);
        }
        std::cout << std::endl;
    }

    return 0;
}
