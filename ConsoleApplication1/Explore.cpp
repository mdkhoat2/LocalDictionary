#include "Explore.h"

int ranNum(int n) {
    // Seed engine
    std::random_device rd;
    // Random number generator
    std::mt19937 gen(rd());
    // Define the distribution for the desired range
    std::uniform_int_distribution<> dis(0, n - 1);
    int randomIndex = dis(gen);
    return randomIndex;
}