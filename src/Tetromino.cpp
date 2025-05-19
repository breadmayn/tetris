#include "Tetromino.hpp"

#include <array>

/*
    static shapes structure which is indexed through <static_cast<int>(BlockState) - 1> which
    will result in an array of 4 elements each element representing the offsets from the position
    for the cells generated for each rotation

    usage: shapes[static_cast<int>(BlockState)][int rotation]
    NOTE: rotation will always be modulo 4
*/
static const std::array<std::array<std::array<sf::Vector2<int>, 4>, 4>, 7> shapes {{
    {{
        // BlockState::I
        {{ {0, -1}, {0, 0}, {0, 1}, {0, 2} }},
        {{ {0, 1}, {1, 1}, {2, 1}, {3, 1} }},
        {{ {1, -1}, {1, 0}, {1, 1}, {1, 2} }},
        {{ {0, 0}, {1, 0}, {2, 0}, {3, 0} }}
    }},
    {{
        // BlockState::O
        {{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }},
        {{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }},
        {{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }},
        {{ {0, 0}, {0, 1}, {1, 0}, {1, 1} }}
    }},
    {{
        // BlockState::T
        {{ {-1, 0}, {0, -1}, {0, 0}, {0, 1} }},
        {{ {-1, 0}, {0, 0}, {0, 1}, {1, 0} }},
        {{ {0, -1}, {0, 0}, {0, 1}, {1, 0} }},
        {{ {-1, 0}, {0, -1}, {0, 0}, {1, 0} }}
    }},
    {{
        // BlockState::S
        {{ {-1, 0}, {-1, 1}, {0, -1}, {0, 0} }},
        {{ {-1, 0}, {0, 0}, {0, 1}, {1, 1} }},
        {{ {-1, 0}, {-1, 1}, {0, -1}, {0, 0} }},
        {{ {-1, -1}, {0, -1}, {0, 0}, {1, 0} }}
    }},
    {{
        // BlockState::Z
        {{ {-1, -1}, {-1, 0}, {0, 0}, {0, 1} }},
        {{ {-1, 1}, {0, 0}, {0, 1}, {1, 0} }},
        {{ {-1, -1}, {-1, 0}, {0, 0}, {0, 1} }},
        {{ {-1, 0}, {0, -1}, {0, 0}, {1, -1} }}
    }},
    {{
        // BlockState::J
        {{ {-1, -1}, {0, -1}, {0, 0}, {0, 1} }},
        {{ {-1, 1}, {-1, 0}, {0, 0}, {1, 0} }},
        {{ {0, -1}, {0, 0}, {0, 1}, {1, 1} }},
        {{ {-1, 0}, {0, 0}, {1, 0}, {1, -1} }}
    }},
    {{
        // BlockState::L
        {{ {0, -1}, {0, 0}, {0, 1}, {-1, 1} }},
        {{ {-1, 0}, {0, 0}, {1, 0}, {1, 1} }},
        {{ {0, -1}, {0, 0}, {0, 1}, {1, -1} }},
        {{ {-1, -1}, {-1, 0}, {0, 0}, {1, 0} }}
    }}
}};

// constructor
Tetromino::Tetromino(BlockState type): type(type)
{
    if (type == BlockState::O || type == BlockState::I) position = { 0 , 4 };
    else position = { 1 , 4 };
    
    rotationState = 0;
    locked = false;
}

void Tetromino::move(int dx, int dy)
{
    position.x += dx;
    position.y += dy;
}

/*
    Tetromino state getter methods
*/

BlockState Tetromino::getType() const { return type; }

sf::Vector2<int> Tetromino::getPosition() const { return position; }

bool Tetromino::isLocked() const { return locked; }

std::array<sf::Vector2<int>, 4> Tetromino::getBlockOffsets() const
{
    return shapes[static_cast<int>(type) - 1][rotationState];
}

/*
    Tetromino modifying methods
*/

void Tetromino::setRotationState(int rotationInc)
{
    rotationState = (rotationState + rotationInc) % 4;
}

void Tetromino::lock() { locked = true; }

void Tetromino::moveDown() { move(1, 0); }

void Tetromino::moveUp() { move(-1, 0); }

void Tetromino::moveLeft() { move(0, -1); }

void Tetromino::moveRight() { move(0 ,1); }