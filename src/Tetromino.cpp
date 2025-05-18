#include "Tetromino.hpp"

#include <array>

const std::array<std::array<std::array<sf::Vector2<int>, 4>, 4>, 7> shapes {{
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
        {{ {-1, 1}, {0, 0}, {0, 1}, {1, 1} }},
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

Tetromino::Tetromino(BlockState type): type(type)
{
    if (type == BlockState::O || type == BlockState::I)
        position = { 0 , 4 };
    else position = { 1 , 4};
    
    rotationState = 0;
    prevRotationState = 0;

    locked = false;
}

int Tetromino::getRotationState() { return rotationState; }

bool Tetromino::hasRotated() { return prevRotationState != rotationState; }

bool Tetromino::isLocked() { return locked; }

sf::Vector2<int> Tetromino::getPosition() { return position; }

std::array<sf::Vector2<int>, 4> Tetromino::getBlockOffsets() { return shapes[static_cast<int>(type) - 1][rotationState]; }

BlockState Tetromino::getType() { return type; }

void Tetromino::moveDown() { position.x++; }

void Tetromino::lock() { locked = true; }