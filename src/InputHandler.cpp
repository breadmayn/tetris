#include "InputHandler.hpp"

#include <unordered_map>

static float dasDelay = 0.167f;
static float arrRate = 0.05f;

// temp user preferences
static std::unordered_map<sf::Keyboard::Scan, Action> userControls {
    {sf::Keyboard::Scan::Left, Action::LEFT},
    {sf::Keyboard::Scan::Right, Action::RIGHT},
    {sf::Keyboard::Scan::Space, Action::HARDDROP},
    {sf::Keyboard::Scan::Down, Action::SOFTDROP},
    {sf::Keyboard::Scan::X, Action::CW_ROTATE},
    {sf::Keyboard::Scan::Z, Action::CCW_ROTATE},
    {sf::Keyboard::Scan::C, Action::DOUBLE_ROTATE},
    {sf::Keyboard::Scan::LShift, Action::HOLD}
};

InputHandler::InputHandler(sf::RenderWindow& window, GameBoard& board)
    : window(&window)
    , board(&board)
    , softDropping(false)
{
    // NOTE: probably need to update this for user control preferences
    horizHeld = std::nullopt;

    softClock = sf::Clock();
    dasClock = sf::Clock();

    das = false;
}

bool InputHandler::isSoftDropping() const { return softDropping; }

bool InputHandler::handleEvent(const std::optional<sf::Event>& event)
{
    // handle the closing event
    if (event->is<sf::Event::Closed>()) window->close();

    // handle keyboard inputs
    if (event->is<sf::Event::KeyPressed>())
    {
        const auto& keyPressed = event->getIf<sf::Event::KeyPressed>();

        // ensure only user controls will do something
        if (userControls.find(keyPressed->scancode) == userControls.end()) return false;
        Action action = userControls[keyPressed->scancode];

        // handle the different action cases
        switch (userControls[keyPressed->scancode])
        {
        case Action::LEFT:
            if (board->tryMove(0, -1))
            {
                dasClock.restart();
                das = false;

                horizHeld = keyPressed->scancode;

                return true;
            }
            break;
        case Action::RIGHT:
            if (board->tryMove(0, 1))
            {
                dasClock.restart();
                das = false;

                horizHeld = keyPressed->scancode;

                return true;
            }
            break;
        case Action::HARDDROP:
            board->hardDrop();
            return true;
            break;
        case Action::SOFTDROP:
            if (board->tryMove(1, 0))
            {
                softClock.restart();
                softDropping = true;

                return true;
            }
            break;
        case Action::CW_ROTATE:
            if (board->tryRotate(1)) return true;
            break;
        case Action::CCW_ROTATE:
            if (board->tryRotate(3)) return true;
            break;
        case Action::DOUBLE_ROTATE:
            if (board->tryRotate(2)) return true;
            break;
        case Action::HOLD:
            break;
        default: // error enum is weird
            window->close();
            break;
        }

    }
    else if (event->is<sf::Event::KeyReleased>())
    {
        const auto& keyReleased = event->getIf<sf::Event::KeyReleased>();

        // ensure only user controls will do something
        if (userControls.find(keyReleased->scancode) == userControls.end()) return false;
        Action action = userControls[keyReleased->scancode];

        switch (action)
        {
        case Action::LEFT:
            if (horizHeld.has_value() && *horizHeld == keyReleased->scancode)
            {
                horizHeld = std::nullopt;
                das = false;
            }
            break;
        case Action::RIGHT:
            if (horizHeld.has_value() && *horizHeld == keyReleased->scancode)
            {
                horizHeld = std::nullopt;
                das = false;
            }
            break;
        case Action::SOFTDROP:
            softDropping = false;
            break;
        default:
            break; // should put something here for error catching
        }

    }

    return false;
}

bool InputHandler::handleHeldKeys()
{
    bool didMove { false };
    float duration;

    if (!horizHeld.has_value()) goto HANDLE_SOFT_DROP;

    duration = dasClock.getElapsedTime().asSeconds();

    if (!das)
    {
        if (duration < dasDelay) goto HANDLE_SOFT_DROP;

        das = true;
    }
    else
    {
        if (duration < arrRate) goto HANDLE_SOFT_DROP;
    }

    if (*horizHeld == sf::Keyboard::Scan::Left)
    {
        didMove |= board->tryMove(0, -1);
    }
    else if (*horizHeld == sf::Keyboard::Scan::Right)
    {
        didMove |= board->tryMove(0, 1);
    }

HANDLE_SOFT_DROP:
    if (!softDropping) return didMove;

    duration = softClock.getElapsedTime().asSeconds();
    if (duration < arrRate) return didMove;

    didMove |= board->tryMove(1, 0);
    
    return didMove;
}
