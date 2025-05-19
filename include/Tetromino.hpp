#pragma once

#include <SFML/System/Vector2.hpp>
#include <vector>

#include "define.hpp"

class Tetromino {
private:
    BlockState type;
    sf::Vector2<int> position; // current position of the origin block
    int rotationState; // index for which rotation offsets we will use [0, 3]
    int prevRotationState; // index for the previous rotation state/index
    bool locked;

public:
    Tetromino(BlockState type);

    void setRotationState(int rotationInc);

    std::array<sf::Vector2<int>, 4> getRotation(int rotationInc);

    bool isLocked();

    sf::Vector2<int> getPosition();

    std::array<sf::Vector2<int>, 4> getBlockOffsets();

    BlockState getType();

    void moveDown();

    void moveUp();

    void lock();

    void move(bool isLeft);
};