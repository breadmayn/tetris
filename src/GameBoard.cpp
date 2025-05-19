#include "GameBoard.hpp"

bool GameBoard::tryToMoveDown(Tetromino& block)
{
    auto [startingX, startingY] = block.getPosition();

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
    auto [startingX, startingY] = block.getPosition();

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;

        grid[newX][newY].state = block.getType();
    }

    block.lock();
}

bool GameBoard::tryToMoveHoriz(Tetromino& block, bool isLeft)
{
    auto [startingX, startingY] = block.getPosition();

    startingY = isLeft ? startingY - 1 : startingY + 1;

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;

        // out of bounds and collision checking

        if (newY >= numCols || newY < 0 || grid[newX][newY].state != BlockState::Empty) return false;
    }

    // if all pieces are not colliding with others and in bounds then move the block
    block.move(isLeft);
    return true;
}

bool GameBoard::tryRotate(Tetromino& block, int rotation)
{
    auto [startingX, startingY] = block.getPosition();

    int newX, newY;

    for (const auto& [incX, incY] : block.getRotation(rotation))
    {
        newX = startingX + incX;
        newY = startingY + incY;

        // out of bounds and collision checking
        if (newX >= numRows) return false;

        if (newY < 0 || newY >= numCols || grid[newX][newY].state != BlockState::Empty) return false;
    }

    block.setRotationState(rotation);
    return true;
}

bool GameBoard::canPlace(Tetromino& block)
{
    auto [startingX, startingY] = block.getPosition();

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;

        if (newX < 0 || newX >= numRows || newY < 0 || newY >= numCols) return false;

        if (grid[newX][newY].state != BlockState::Empty) return false;
    }

    return true;
}