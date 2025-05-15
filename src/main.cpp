#include <SFML/Graphics.hpp>

#include "GameBoard.hpp"
#include "Renderer.hpp"

bool hasChanged { true };

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Tetris1.0");
    window.setFramerateLimit(144);

    // setting window background color
    window.clear(sf::Color(100, 100, 100));

    // create GameBoard object for game logic
    GameBoard board;

    // create Renderer object and render out the initial gameboard
    Renderer renderer(45);
    renderer.drawInitialGameBoard(window, board);

    while (window.isOpen())
    {
        // while loop checking for events (inputs)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        
        // update the grid accordinly if it has changed
        if (hasChanged)
        {
            hasChanged = false;

            window.display();
        }
    }
}
