#include "Randomizer.hpp"

#include <algorithm>

Randomizer::Randomizer(): rng(std::random_device{}()), index(0) { refillBag(); }

void Randomizer::refillBag()
{
    bag = {
        BlockState::I,
        BlockState::O,
        BlockState::T,
        BlockState::J,
        BlockState::L,
        BlockState::S,
        BlockState::Z
    };

    std::shuffle(bag.begin(), bag.end(), rng);
    index = 0;
}

BlockState Randomizer::next()
{
    if (index >= bag.size()) refillBag();

    return bag[index++];
}