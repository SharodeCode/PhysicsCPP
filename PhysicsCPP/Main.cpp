#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Entities/Portal.h"
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>
#include <Engine/Game.h>

constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 800;
constexpr int FRAME_RATE = 60;
constexpr int SUB_STEPS = 8;

static 
bool shootBalls = true;

int main()
{
    sf::RenderWindow windowMine = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
    windowMine.setFramerateLimit(FRAME_RATE);

    PhysicsEngine ps = PhysicsEngine();
    ps.subStepCount = SUB_STEPS;

    UI ui = UI(&windowMine, &ps);
    Renderer renderer(&windowMine, &ui);

    float subStepRate = (1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f);

	InputManager inputManager(ps, ui, windowMine);

    Game game(windowMine, ps, renderer, ui, inputManager);

	game.run();

    return 0;
}
