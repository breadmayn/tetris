#include "define.hpp"

const std::unordered_map<BlockState, sf::Color> colorMap {
    {BlockState::Empty, sf::Color(50, 50, 50)},
    {BlockState::I, sf::Color::Cyan},
    {BlockState::O, sf::Color::Yellow},
    {BlockState::T, sf::Color(128, 0, 128)},
    {BlockState::S, sf::Color::Green},
    {BlockState::Z, sf::Color::Red},
    {BlockState::J, sf::Color::Blue},
    {BlockState::L, sf::Color(255, 165, 0)}
};

