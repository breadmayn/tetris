#pragma once

#include <vector>

#include "define.hpp"
#include "Tetromino.hpp"

class GameBoard {
private:
    std::vector<std::vector<Block>> grid;

public:
    GameBoard(): grid(numRows, std::vector<Block>(numCols)) {}

    inline const std::vector<std::vector<Block>>& getGrid() const { return grid; }

    bool tryToMoveDown(Tetromino& block) const;

    void lockPiece(Tetromino& block);

    bool tryToMoveHoriz(Tetromino& block, bool isLeft) const;

    bool tryRotate(Tetromino& block, int rotation) const;

    bool canPlace(Tetromino& block) const;

    Tetromino getGhostPiece(const Tetromino& block) const;

    void hardDrop(Tetromino& block);
};
