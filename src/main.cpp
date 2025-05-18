#include <SFML/Graphics.hpp>
#include <queue>

#include "GameBoard.hpp"
#include "Renderer.hpp"
#include "Randomizer.hpp"
#include "Tetromino.hpp"

bool hasChanged { true };
float currentTickRate = 0.5f;

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Tetris1.0");
    window.setFramerateLimit(144);

    // create GameBoard object for game logic
    GameBoard board;

    // create Renderer object and render out the initial gameboard
    Renderer renderer(window, 45);

    // create Randomizer which utilizes the 7-bag randomizer algorithm used in modern tetris
    Randomizer tetrominoGenerator;

    // grab the very first piece and render onto the screen
    Tetromino currentBlock(tetrominoGenerator.next());

    sf::Clock clock;

    while (window.isOpen())
    {
        // while loop checking for events (inputs)
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) window.close();
            
            // handle keyboard inputs
            if (event->is<sf::Event::KeyPressed>())
            {
                const auto& keyEvent = event->getIf<sf::Event::KeyPressed>();

                // TODO: add the keyboard input handling
                // NOTE: possibly make this parse through a map of user control preferences
            }
        }

        // generate and render new piece on start or after locking prev piece into place
        if (currentBlock.isLocked())
        {
            currentBlock = Tetromino(tetrominoGenerator.next());
            
            hasChanged = true;
            clock.restart(); // reset clock?
        }

        // handle the tickrate of the game by dropping pieces
        if (clock.getElapsedTime().asSeconds() >= currentTickRate)
        {
            // if we cannot move the current block down, lock it in place
            if (board.tryToMoveDown(currentBlock))
            {
                hasChanged = true;
                clock.restart();
            }
            else board.lockPiece(currentBlock);
        }

        
        // update the grid accordinly if it has changed
        // NOTE: this might be wrong for getting game state to stay the same
        if (hasChanged)
        {
            hasChanged = false;

            window.clear(sf::Color(100, 100, 100));

            renderer.drawInitialGameBoard(window, board);
            renderer.drawFallingTetromino(window, currentBlock);

            window.display();
        }
    }
}
