#include "InputHandler.hpp"

#include <unordered_map>

static float dasDelay = 0.167f;
static float arrRate = 0.05f;

// controls enum
enum class Action {
    LEFT, RIGHT, HARD, SOFT, CW_ROTATE, CCW_ROTATE, DOUBLE_ROTATE, HOLD
};

// temp user preferences
static std::unordered_map<sf::Keyboard::Scan, Action> userControls {
    {sf::Keyboard::Scan::Left, Action::LEFT},
    {sf::Keyboard::Scan::Right, Action::RIGHT},
    {sf::Keyboard::Scan::Space, Action::HARD},
    {sf::Keyboard::Scan::Down, Action::SOFT},
    {sf::Keyboard::Scan::X, Action::CW_ROTATE},
    {sf::Keyboard::Scan::Z, Action::CCW_ROTATE},
    {sf::Keyboard::Scan::C, Action::DOUBLE_ROTATE},
    {sf::Keyboard::Scan::LShift, Action::HOLD}
};

InputHandler::InputHandler(sf::RenderWindow& window, GameBoard& board, Tetromino& block):
    window(&window), board(&board), currentBlock(&block), softDropping(false)
{
    // NOTE: change once user control preferences are implemented
    for (const auto& [input, _] : userControls)
    {
        keyHeldTimers[input] = sf::Clock();
    }
}

bool InputHandler::isSoftDropping() const { return softDropping; }

bool InputHandler::update()
{
    bool didMove { false };

    for (const auto& key : held)
    {
        float duration = keyHeldTimers[key].getElapsedTime().asSeconds();

        if (das.find(key) == das.end())
        {
            // we haven't waited for dasDelay yet
            if (duration < dasDelay) continue;
            
            // insert into das tracker
            das.insert(key);
        }
        else
        {
            // we have already waited dasDelay
            if (duration < arrRate) continue;
        }

        switch (userControls[key])
        {
        case Action::LEFT:
            didMove |= board->tryMoveHoriz(*currentBlock, true);
            keyHeldTimers[key].restart();
            break;
        case Action::RIGHT:
            didMove |= board->tryMoveHoriz(*currentBlock, false);
            keyHeldTimers[key].restart();
            break;
        case Action::HARD:
            board->hardDrop(*currentBlock);
            didMove |= true;
            keyHeldTimers[key].restart();
            break;
        case Action::SOFT:
            didMove |= board->tryMoveDown(*currentBlock);
            keyHeldTimers[key].restart();
            break;
        case Action::CW_ROTATE:
            didMove |= board->tryRotate(*currentBlock, 1);
            keyHeldTimers[key].restart();
            break;
        case Action::CCW_ROTATE:
            didMove |= board->tryRotate(*currentBlock, 3);
            keyHeldTimers[key].restart();
            break;
        case Action::DOUBLE_ROTATE:
            didMove |= board->tryRotate(*currentBlock, 2);
            keyHeldTimers[key].restart();
            break;
        case Action::HOLD:
            break;
        default: // error enum is weird
            window->close();
            break;
        }
    }

    return didMove;
}

bool InputHandler::handleEvent(const std::optional<sf::Event>& event)
{
    // handle the closing event
    if (event->is<sf::Event::Closed>()) window->close();

    // handle keyboard inputs
    if (event->is<sf::Event::KeyPressed>())
    {
        const auto& keyPressed = event->getIf<sf::Event::KeyPressed>();

        // register in held and restart timers incase the KeyPress is held
        held.insert(keyPressed->scancode);
        keyHeldTimers[keyPressed->scancode].restart();

        // perform the first event functionality
        switch (userControls[keyPressed->scancode])
        {
        case Action::LEFT:
            if (board->tryMoveHoriz(*currentBlock, true)) return true;
            break;
        case Action::RIGHT:
            if (board->tryMoveHoriz(*currentBlock, false)) return true;
            break;
        case Action::HARD:
            board->hardDrop(*currentBlock);
            return true;
            break;
        case Action::SOFT:
            if (board->tryMoveDown(*currentBlock))
            {
                softDropping = true;
                return true;
            }
            break;
        case Action::CW_ROTATE:
            if (board->tryRotate(*currentBlock, 1)) return true;
            break;
        case Action::CCW_ROTATE:
            if (board->tryRotate(*currentBlock, 3)) return true;
            break;
        case Action::DOUBLE_ROTATE:
            if (board->tryRotate(*currentBlock, 2)) return true;
            break;
        case Action::HOLD:
            break;
        default: // error enum is weird
            window->close();
            break;
        }

        // return false;
    }
    else if (event->is<sf::Event::KeyReleased>())
    {
        const auto& keyReleased = event->getIf<sf::Event::KeyReleased>()->scancode;

        // un-register in held
        held.erase(keyReleased);

        // un-register in tas tracker
        das.erase(keyReleased);

        softDropping = false;
    }

    return false;
}