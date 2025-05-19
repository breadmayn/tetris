#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

#include "GameBoard.hpp"
#include "Tetromino.hpp"

class Renderer {
private:
    const sf::Color gridLineColor { sf::Color::Black };
    const float gridLineWidth { 2.0f };
    
    float cellSize; // passed in argument for cell size

    float xOffset;
    float yOffset;

    float cellLen; // the actual length of each side of the cell (cellSize - gridLineWidth)

public:
    Renderer(sf::RenderWindow& window, float size);

    void drawInitialGameBoard(sf::RenderWindow& window, const GameBoard& board);

    void drawTetromino(sf::RenderWindow& window, Tetromino& block, bool isGhost);
};
