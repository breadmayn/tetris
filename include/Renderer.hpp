#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>

#include "GameBoard.hpp"
#include "Tetromino.hpp"

class Renderer {
private:
    sf::RenderWindow* window; // pointer to window object to reduce passing in as arg
    float cellSize; // passed in argument with desired cell length

    // offsets used to place the GameBoard in the center of the window
    float xOffset;
    float yOffset;

    sf::Vector2<float> cellDimensions;

    /*
        private rendering helper methods
    */

    void drawGameBoardState(const GameBoard& board) const;

    void drawTetromino(const Tetromino& block, bool isGhost) const;

public:
    Renderer(sf::RenderWindow& window, float size);

    void render(const GameBoard& board) const;
};
