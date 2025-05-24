#pragma once

#include <vector>

#include "define.hpp"
#include "Tetromino.hpp"
#include "Randomizer.hpp"

class GameBoard {
private:
    // grid of 10x20 that backs the GameBoard
    std::array<std::array<Block, 10>, 20> grid;
    std::array<int, 20> rowCounters;

    Randomizer tetrominoGenerator;
    Tetromino currentTetromino;

    bool toppedOut;

    // private member helper methods
    bool canPlace(const Tetromino& block) const;

public:
    // default constructor
    GameBoard();

    // getter methods
    const std::array<std::array<Block, 10>, 20>& getGrid() const;
    const Tetromino& getTetromino() const;
    bool hasToppedOut() const;

    /*
        Tetromino handling methods
    */

    bool tryMove(int dx, int dy);
    bool tryRotate(int rotation);

    Tetromino getGhost() const;

    /*
        GameBoard modifying Tetromino methods
    */
    void tryClearRows();
    void lockTetromino(const Tetromino& block);
    void hardDrop();
};
