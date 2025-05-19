#pragma once

#include <vector>

#include "define.hpp"
#include "Tetromino.hpp"

class GameBoard {
private:
    // grid of 10x20 that backs the GameBoard
    std::array<std::array<Block, 10>, 20> grid;

public:
    // default constructor
    GameBoard();

    // getter method for the backing grid
    const std::array<std::array<Block, 10>, 20>& getGrid() const;

    /*
        Tetromino handling methods
    */
    bool canPlace(Tetromino& block) const;

    bool tryMoveDown(Tetromino& block) const;
    bool tryMoveHoriz(Tetromino& block, bool direction) const;
    bool tryRotate(Tetromino& block, int rotation) const;

    Tetromino getGhostPiece(const Tetromino& block) const;

    /*
        GameBoard modifying Tetromino methods
    */
    void lockTetromino(Tetromino& block);
    void hardDrop(Tetromino& block);
};
