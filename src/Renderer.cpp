#include "Renderer.hpp"
#include "define.hpp"

#include <SFML/Graphics/RectangleShape.hpp>

Renderer::Renderer(sf::RenderWindow& window, float size): cellSize(size + gridLineWidth)
{
    // grabbing window dimensions for dynamic sizing
    auto gridDimensions = window.getSize();
    auto [width, height] = gridDimensions;

    // calculate offsets needed to place grid in the center of window
    float gridWidth = numCols * cellSize;
    float gridHeight = numRows * cellSize;

    xOffset = (width - gridWidth) / 2.0f;
    yOffset = (height - gridHeight) / 2.0f;

    cellLen = cellSize - gridLineWidth;
}

void Renderer::drawInitialGameBoard(sf::RenderWindow& window, const GameBoard& board)
{
    const auto& grid = board.getGrid();

    // creating the cell dimensions based on passed in cellSize
    sf::Vector2<float> cellDimensions { cellLen, cellLen };
    sf::Vector2<float> cellPosition;

    // iterate over the entire grid and render out the initial blocks of the grid
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            sf::RectangleShape cell;

            cellPosition = {
                xOffset + j * cellSize + gridLineWidth / 2,
                yOffset + i * cellSize + gridLineWidth / 2
            };

            cell.setSize(cellDimensions);
            cell.setPosition(cellPosition);
            cell.setFillColor(colorMap.at(grid[i][j].state));

            window.draw(cell);
        }
    }
}

void Renderer::drawTetromino(sf::RenderWindow& window, Tetromino& block, bool isGhost)
{
    auto [startingX, startingY] = block.getPosition();

    sf::Vector2<float> cellDimensions { cellLen, cellLen };
    sf::Vector2<float> cellPosition;

    int newX, newY;

    for (const auto& [incX, incY] : block.getBlockOffsets())
    {
        newX = startingX + incX;
        newY = startingY + incY;
        
        sf::RectangleShape cell;

        cellPosition = {
            xOffset + newY * cellSize + gridLineWidth / 2,
            yOffset + newX * cellSize + gridLineWidth / 2
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

        window.draw(cell);
    }
}
