#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Entities/Portal.h"
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>

constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 800;
constexpr int FRAME_RATE = 60;
constexpr int SUB_STEPS = 8;

static sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
bool shootBalls = true;

static void initialise() {
    window.setFramerateLimit(FRAME_RATE);
}

int main()
{
    initialise();

    PhysicsEngine ps = PhysicsEngine();
    ps.subStepCount = SUB_STEPS;

    // Create a clock to control the movement
    sf::Clock clock = sf::Clock();

    UI ui = UI(&window, &ps);
    Renderer renderer(&window, &ui);

    float subStepRate = (1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f);


    float accumulator = 0.0f;
    float spawnCircleTime = 0.0f;

    static bool lockClick = false;

    sf::Texture texture;
    if (!texture.loadFromFile("./Media/Images/portal.png"))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    Button::buttonType currentButton = Button::buttonType::mute;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        accumulator += deltaTime;

        InputManager inputManager(ps, ui, window);

		inputManager.handleInput();

        ps.update(subStepRate);

        renderer.render(ps, deltaTime);
    }

    return 0;
}
