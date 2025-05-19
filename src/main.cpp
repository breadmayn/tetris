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

                // NOTE: possibly make this parse through a map of user control preferences
                if (keyEvent->scancode == sf::Keyboard::Scan::Left)
                {
                    if (board.tryMoveHoriz(currentBlock, true)) hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Right)
                {
                    if (board.tryMoveHoriz(currentBlock, false)) hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::X)
                {
                    if (board.tryRotate(currentBlock, 1)) hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Z)
                {
                    if (board.tryRotate(currentBlock, 3)) hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::C)
                {
                    if (board.tryRotate(currentBlock, 2)) hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Space)
                {
                    board.hardDrop(currentBlock);
                    hasChanged = true;
                }
                else if (keyEvent->scancode == sf::Keyboard::Scan::Down)
                {
                    
                }
            }
        }

        // generate and render new piece on start or after locking prev piece into place
        if (currentBlock.isLocked())
        {
            currentBlock = Tetromino(tetrominoGenerator.next());
            if (!board.canPlace(currentBlock)) window.close();

            hasChanged = true;
            clock.restart();
        }

        // handle the tickrate of the game by dropping pieces
        if (clock.getElapsedTime().asSeconds() >= currentTickRate)
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
