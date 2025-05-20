#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include <unordered_set>
#include <optional>

#include "GameBoard.hpp"

class InputHandler {
private:
    sf::RenderWindow* window;
    GameBoard* board;
    Tetromino* currentBlock;

    // input states
    bool softDropping;

    // data structures for tracking inputs
    std::unordered_set<sf::Keyboard::Scancode> held; // isValid for keyHeldTimers
    std::unordered_map<sf::Keyboard::Scancode, sf::Clock> keyHeldTimers; // held keys

    // tracker if the key has already been held for dasDelay
    std::unordered_set<sf::Keyboard::Scancode> das;
public:
    // constructor
    InputHandler(sf::RenderWindow& window, GameBoard& board, Tetromino& block);

    // input state getter methods
    bool isSoftDropping() const;
    
    // event handler
    bool handleEvent(const std::optional<sf::Event>& event);

    bool update();
};