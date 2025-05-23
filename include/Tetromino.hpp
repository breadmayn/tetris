#pragma once

#include <SFML/System/Vector2.hpp>

#include "define.hpp"

class Tetromino {
private:
    BlockState type; // denotes current Tetromino

    // single coordinate that will be the base of where all the cells should be placed
    sf::Vector2<int> position;

    int rotationState; // index of which rotation state current Tetromino is in (within shapes structure)

public:
    // default constructor
    Tetromino(BlockState type);

    /*
        Tetromino state getter methods
    */
    
    BlockState getType() const;
    sf::Vector2<int> getPosition() const;

    std::array<sf::Vector2<int>, 4> getBlockOffsets() const;
    
    /*
        Tetromino modifying methods
    */

    void move(int dx, int dy);

    void setRotationState(int rotationInc);
};
