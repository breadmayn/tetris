#include <SFML/Graphics.hpp>
#include <queue>

#include "GameBoard.hpp"
#include "Renderer.hpp"
#include "Randomizer.hpp"
#include "Tetromino.hpp"
#include "InputHandler.hpp"

static bool hasChanged { true };
static float gravityTickRate = 0.75f;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Tetris1.0");

    window.setFramerateLimit(144);
    window.setKeyRepeatEnabled(false); // disabling and creating structures to handle DAS and ARR

    // create GameBoard object for game logic
    GameBoard board;

    // create Renderer object and render out the initial gameboard
    Renderer renderer(window, 45);

    // create Randomizer which utilizes the 7-bag randomizer algorithm used in modern tetris
    Randomizer tetrominoGenerator;

    // grab the very first piece and render onto the screen
    Tetromino currentBlock(tetrominoGenerator.next());

    // InputHandler object to handle all user controls during the game
    InputHandler inputHandler(window, board, currentBlock);

    sf::Clock clock;

    while (window.isOpen())
    {
        // while loop checking for events (inputs)
        while (const std::optional event = window.pollEvent())
        {
            // hasChanged = inputHandler.handleEvent(event); // this line causes rotation delay?
            hasChanged |= inputHandler.handleEvent(event);
        }

        // handling held keys
        hasChanged |= inputHandler.handleHeldKeys();

        // generate and render new piece on start or after locking prev piece into place
        if (currentBlock.isLocked())
        {
            currentBlock = Tetromino(tetrominoGenerator.next());
            if (!board.canPlace(currentBlock)) window.close();

            hasChanged = true;
            clock.restart();
        }

        // handle the tickrate of the game by dropping pieces
        if (!inputHandler.isSoftDropping() && clock.getElapsedTime().asSeconds() >= gravityTickRate)
        {
            // if we cannot move the current block down, lock it in place
            if (board.tryMoveDown(currentBlock))
            {
                hasChanged = true;
                clock.restart();
            }
            else board.lockTetromino(currentBlock);
        }
        
        // update the grid accordinly if it has changed
        if (hasChanged)
        {
            hasChanged = false;
            
            renderer.render(board, currentBlock);
        }
    }
}
