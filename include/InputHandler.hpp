#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include <unordered_set>
#include <optional>

#include "define.hpp"
#include "GameBoard.hpp"

class InputHandler {
private:
    sf::RenderWindow* window;
    GameBoard* board;
    Tetromino* currentBlock;
    
    // member types that contain held keystroke states
    bool softDropping;
    std::optional<sf::Keyboard::Scan> horizHeld; // Action::LEFT and Action::RIGHT

    // clocks for held keystrokes
    sf::Clock softClock;
    sf::Clock dasClock;

    // flag to denote if we have held for dasTime for horizontal movement inputs
    bool das;

public:
    // constructor
    InputHandler(sf::RenderWindow& window, GameBoard& board, Tetromino& block);

    // input state getter methods
    bool isSoftDropping() const;
    
    // event handler
    bool handleEvent(const std::optional<sf::Event>& event);

    bool handleHeldKeys();
    
};