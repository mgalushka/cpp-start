#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
    std::random_device rseed;
    static std::mt19937 generator(rseed());
    std::uniform_int_distribution<int> distribution(0, 100);

    for (int16_t ii = 0; ii < 100; ii++) {
        std::cout << distribution(generator) << std::endl;
    }
    return 0;
}