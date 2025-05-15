#pragma once

#include <vector>

#include "define.hpp"

class GameBoard {
private:
    std::vector<std::vector<Block>> grid;

public:
    GameBoard(): grid(numRows, std::vector<Block>(numCols)) {}

    inline const std::vector<std::vector<Block>>& getGrid() const { return grid; }
};