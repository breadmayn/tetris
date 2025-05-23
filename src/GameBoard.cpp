#include "GameBoard.hpp"

// default constructor definition
GameBoard::GameBoard()
    : grid(std::array<std::array<Block, 10>, 20>())
    , rowCounters({ 0 })
    , tetrominoGenerator(Randomizer())
    , currentTetromino(Tetromino(tetrominoGenerator.next()))
    , toppedOut(false)
{}

/*
    Class getter methods
*/
const std::array<std::array<Block, 10>, 20>& GameBoard::getGrid() const { return grid; }
const Tetromino& GameBoard::getTetromino() const { return currentTetromino; }
bool GameBoard::hasToppedOut() const { return toppedOut; }

/*
    Tetromino handling methods
*/

bool GameBoard::canPlace(const Tetromino& block) const
{
    // grab the origin point where we will use offset from for mino collision and bounds checking
    auto [startingX, startingY] = block.getPosition();

    // iterate over all of the offset coordinates
    for (const auto& [dx, dy] : block.getBlockOffsets())
    {
        int x = startingX + dx;
        int y = startingY + dy;

        // bounds checking x
        if (x < 0 || x >= numRows) return false;

        // bounds checking y
        if (y < 0 || y >= numCols) return false;

        // checking for collisions with other minos
        if (grid[x][y].state != BlockState::Empty) return false;
    }

    return true;
}

bool GameBoard::tryMove(int xOffset, int yOffset)
{
    // make a copy of currentTetromino for modification
    Tetromino temp = currentTetromino;

    // perform the move operation
    temp.move(xOffset, yOffset);

    // if the current move operation cannot be placed then return false
    if (!canPlace(temp)) return false;

    // the move operation is valid so we can modify currentTetromino
    currentTetromino.move(xOffset, yOffset);
    return true;
}

bool GameBoard::tryRotate(int rotation)
{
    // make a copy of the currentTetromino for modification
    Tetromino temp = currentTetromino;

    // perform the rotation
    temp.setRotationState(rotation);

    // if the current rotation operation cannot be placed then return false
    if (!canPlace(temp)) return false;

    // the rotation operation is valid so we can modify currentTetromino
    currentTetromino.setRotationState(rotation);
    return true;
}

Tetromino GameBoard::getGhost() const
{
    // make a copy of currentTetromino to move all the way down the board
    Tetromino ghost = currentTetromino;

    while (canPlace(ghost)) ghost.move(1, 0);

    // move one row up
    ghost.move(-1, 0);
    return ghost;
}

void GameBoard::tryClearRows()
{
    int row { numRows - 1};

    // iterate over all the rows and find the one that is filled
    while (row >= 0)
    {
        // check to see if the row is filled
        if (rowCounters[row] != 10)
        {
            row--;
            continue;
        }

        // row is filled so propagate the row and its counter to the top
        for (int r = row; r > 0; r--)
        {
            grid[r] = grid[r - 1];
            rowCounters[r] = rowCounters[r - 1];
        }

        // clear the top row and reset the counter to 0
        grid[0] = std::array<Block, 10>();
        rowCounters[0] = 0;

        // dont decrement row because multi-line clearing
    }
}

void GameBoard::lockTetromino(Tetromino& block)
{
    // get the origin position of the block
    auto [startingX, startingY] = block.getPosition();

    bool fullRow { false };

    // iterate over the offsets for the minos
    for (const auto& [dx, dy] : block.getBlockOffsets())
    {
        int x = startingX + dx;
        int y = startingY + dy;

        grid[x][y].state = block.getType();

        // update rowCounters
        rowCounters[x]++;
        if (rowCounters[x] == 10) fullRow = true;
    }

    // now that the block is placed onto the board, check to clear the row
    if (fullRow) tryClearRows();

    // generate a new piece
    currentTetromino = Tetromino(tetrominoGenerator.next());
}

void GameBoard::hardDrop()
{
    // the ghost piece is where the hard-dropped piece will go
    Tetromino ghost = getGhost();

    // lock the ghost piece
    lockTetromino(ghost);
}