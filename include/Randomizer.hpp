#pragma once

#include <random>
#include <vector>

#include "define.hpp"

class Randomizer {
private:
    std::mt19937 rng;
    std::vector<BlockState> bag;
    size_t index;

    void refillBag();

public:
    Randomizer();

    BlockState next();
};