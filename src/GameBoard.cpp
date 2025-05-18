#include "GameBoard.hpp"

bool GameBoard::tryToMoveDown(Tetromino& block)
{
    auto currentPos = block.getPosition();
    auto [startingX, startingY] = currentPos;

    startingX++; // try to move this down

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;

        // out of bounds and collision checking
        if (newX >= numRows || grid[newX][newY].state != BlockState::Empty) return false;
    }

    // if all pieces are not colliding with others and in bounds then move the block down
    block.moveDown();
    return true;
}

void GameBoard::lockPiece(Tetromino& block)
{
    auto currentPos = block.getPosition();
    auto [startingX, startingY] = currentPos;

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;

        grid[newX][newY].state = block.getType();
    }

    block.lock();
}