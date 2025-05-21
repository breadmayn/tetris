#include "GameBoard.hpp"

using gridType = std::array<std::array<Block, 10>, 20>;

// default constructor definition
GameBoard::GameBoard(): grid(gridType())
{
    rowCounters = { 0 };
}

// getter method for the backing grid
const gridType& GameBoard::getGrid() const { return grid; }

/*
    Tetromino handling methods
*/
bool GameBoard::canPlace(Tetromino& block) const
{
    auto [startingX, startingY] = block.getPosition();

    for (const auto& [dx, dy] : block.getBlockOffsets())
    {
        int newX = startingX + dx;
        int newY = startingY + dy;

        // checking x coordinate bounds
        if (newX < 0 || newX >= numRows) return false;

        // checking y coordinate bounds
        if (newY < 0 || newY >= numCols) return false;

        // checking if the spot is empty on the grid
        if (grid[newX][newY].state != BlockState::Empty) return false;
    }

    return true;
}

bool GameBoard::tryMoveDown(Tetromino& block) const
{
    // first make a copy of the block so we don't modify the original
    Tetromino temp = block;
    temp.moveDown(); // move the temp Tetromino down one

    // check if the new position is valid
    if (!canPlace(temp)) return false;

    // we can place a row lower so move the original block down
    block.moveDown();
    return true;
}

// direction: true -> left, false -> right
bool GameBoard::tryMoveHoriz(Tetromino& block, bool direction) const
{
    // first make a copy of the block so we don't modify the original
    Tetromino temp = block;

    // move the temp Tetromino to the left or right
    if (direction) temp.moveLeft();
    else temp.moveRight();

    // check if the new position is valid
    if (!canPlace(temp)) return false;

    // we can place at the new position so update the original block
    if (direction) block.moveLeft();
    else block.moveRight();

    return true;
}

bool GameBoard::tryRotate(Tetromino& block, int rotation) const
{
    // first make a copy of the block so we don't modify the original
    Tetromino temp = block;

    // rotate the temp block given the int rotation
    temp.setRotationState(rotation);

    // check if the rotation is valid
    if (!canPlace(temp)) return false;

    // the rotation is valid so apply to the original
    block.setRotationState(rotation);
    return true;
}

Tetromino GameBoard::getGhostPiece(const Tetromino& block) const
{
    Tetromino ghost = block; // copy

    while (canPlace(ghost)) ghost.moveDown();

    ghost.moveUp();

    return ghost;
}

/*
    GameBoard modifying Tetromino methods
*/

void GameBoard::tryClearRows()
{
    int row { numRows - 1 };

    // loop through all of the rows and find a full one
    while (row >= 0)
    {
        if (rowCounters[row] != 10)
        {
            row--;
            continue;
        }

        // propagate the full row and its counter to the top row
        for (int r = row; r > 0; r--)
        {
            grid[r] = grid[r - 1];
            rowCounters[r] = rowCounters[r - 1];
        }

        // clear the top row and its counter
        grid[0] = std::array<Block, 10>();
        rowCounters[0] = 0;

        // dont decrement row because multi-line clearing
    }
}

void GameBoard::lockTetromino(Tetromino& block)
{
    auto [startingX, startingY] = block.getPosition();

    for (const auto& [dx, dy] : block.getBlockOffsets())
    {
        int newX = startingX + dx;
        int newY = startingY + dy;

        grid[newX][newY].state = block.getType();

        // update rowCounters
        rowCounters[newX]++;
    }

    block.lock();

    // now that the block is locked in place, check for row clearing
    tryClearRows();
}

void GameBoard::hardDrop(Tetromino& block)
{
    Tetromino ghost = getGhostPiece(block);

    lockTetromino(ghost);
    block.lock(); // locking to force new piece to generate
}