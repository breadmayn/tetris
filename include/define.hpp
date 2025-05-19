#pragma once

#include <SFML/Graphics/Color.hpp>

#include <unordered_map>
#include <utility>

constexpr unsigned int numRows = 20;
constexpr unsigned int numCols = 10;

enum class BlockState { Empty, I, O, T, S, Z, J, L };

struct Block {
    BlockState state;

    Block(): state(BlockState::Empty) {}
};