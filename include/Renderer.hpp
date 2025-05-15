#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "GameBoard.hpp"

class Renderer {
private:
    const sf::Color gridLineColor { sf::Color::Black };
    const float gridLineWidth { 2.0f };
    
    float cellSize;

public:
    Renderer(float size): cellSize(size + gridLineWidth) {}

    void drawInitialGameBoard(sf::RenderWindow& window, const GameBoard& board);
};