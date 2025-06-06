#include <SFML/Graphics.hpp>
#include <queue>

#include "GameBoard.hpp"
#include "Renderer.hpp"
#include "InputHandler.hpp"

static bool hasChanged { true };
static float gravityTickRate = 0.75f;

int main()
{
    // create and initialize the sfml window
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Tetris1.0");

    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false); // disabling and creating structures to handle DAS and ARR

    // create GameBoard object for game logic
    GameBoard board;

    // create Renderer object and render out the initial gameboard
    Renderer renderer(window, 45);

    // InputHandler object to handle all user controls during the game
    InputHandler inputHandler(window, board);

    sf::Clock clock;

    while (window.isOpen())
    {
        // while loop checking for events (inputs)
        while (const std::optional event = window.pollEvent())
            hasChanged |= inputHandler.handleEvent(event);

        // handling held keys
        hasChanged |= inputHandler.handleHeldKeys();

        // handle the tickrate of the game by dropping pieces
        if (!inputHandler.isSoftDropping() && clock.getElapsedTime().asSeconds() >= gravityTickRate)
        {
            // if we cannot move the current block down, lock it in place
            if (board.tryMove(1, 0))
            {
                hasChanged = true;
                clock.restart();
            }
            else board.lockTetromino(board.getTetromino());
        }
        
        // update the grid accordinly if it has changed
        if (hasChanged)
        {
            hasChanged = false;
            
            renderer.render(board);
        }
    }
}
