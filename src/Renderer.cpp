#include "Renderer.hpp"
#include "define.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

/*
    ColorMap used to figure out what color to make each cell given its BlockState
*/
static const std::unordered_map<BlockState, sf::Color> colorMap {
    {BlockState::Empty, sf::Color(50, 50, 50)},
    {BlockState::I, sf::Color::Cyan},
    {BlockState::O, sf::Color::Yellow},
    {BlockState::T, sf::Color(128, 0, 128)},
    {BlockState::S, sf::Color::Green},
    {BlockState::Z, sf::Color::Red},
    {BlockState::J, sf::Color::Blue},
    {BlockState::L, sf::Color(255, 165, 0)}
};

Renderer::Renderer(sf::RenderWindow& window, float size): window(&window), cellSize(size)
{
    // grab window dimensions
    auto [windowWidth, windowHeight] = window.getSize();

    // calculating grid dimensions

    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    xOffset = (windowWidth - gridWidth) / 2.0f;
    yOffset = (windowHeight - gridHeight) / 2.0f;

    cellDimensions = { cellSize, cellSize };
}

void Renderer::drawGameBoardState(const GameBoard& board) const
{
    const auto& grid = board.getGrid();

    // iterate over the entire grid and render out the locked cells of the grid
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            sf::RectangleShape cell;
            
            // calculate positioning on the window for the current cell
            sf::Vector2<float> cellPosition {
                xOffset + j * cellSize,
                yOffset + i * cellSize
            };

            cell.setSize(cellDimensions);
            cell.setPosition(cellPosition);
            cell.setFillColor(colorMap.at(grid[i][j].state));

            window->draw(cell);
        }
    }
}

void Renderer::drawTetromino(const Tetromino& block, bool isGhost) const
{
    auto [startingX, startingY] = block.getPosition();

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        int newX = startingX + incX;
        int newY = startingY + incY;
        
        sf::RectangleShape cell;

        // calculate position on the window for the current cell
        sf::Vector2<float> cellPosition {
            xOffset + newY * cellSize,
            yOffset + newX * cellSize
        };

        sf::Color cellColor = colorMap.at(block.getType());

        cell.setSize(cellDimensions);
        cell.setPosition(cellPosition);
        if (!isGhost) cell.setFillColor(cellColor);
        else 
        {
            cellColor.a = 80;
            cell.setFillColor(cellColor);
        }

        window->draw(cell);
    }
}

void Renderer::render(const GameBoard& board) const
{
    Tetromino currentTetromino = board.getTetromino();
    window->clear(sf::Color(100, 100, 100));

    drawGameBoardState(board);
    drawTetromino(currentTetromino, false);

    // handle rendering ghost
    Tetromino ghost = board.getGhost();
    drawTetromino(ghost, true);

    window->display();
}