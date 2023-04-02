#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "PhysicsSolver.h"
#include "UI.h"
#include "ParticleSystem.h"

constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 800;
constexpr int FRAME_RATE = 60;
constexpr int SUB_STEPS = 8;

static sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");


static void initialise() {

    window.setFramerateLimit(FRAME_RATE);
}

int main()
{
    initialise();

    // Instantiate the particle system with an initial particle count of 100
    ParticleSystem sparks(100);

    PhysicsSolver ps = PhysicsSolver(&sparks);
    ps.subSteps = SUB_STEPS;

    // Create a clock to control the movement
    sf::Clock clock = sf::Clock();

    UI ui = UI(&window, &ps);

    float subStepRate = 1.0f / (FRAME_RATE * SUB_STEPS);
    float accumulator = 0.0f;
    float spawnCircleTime = 0.0f;

    static bool lockClick = false;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        spawnCircleTime += deltaTime;
        accumulator += deltaTime;

        sparks.update(elapsed);

        if (spawnCircleTime > 0.2)
        {
            ps.spawnCircle(sf::Vector2f(375, 185));
            spawnCircleTime = 0;
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && lockClick == false) {
                lockClick = true;
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                ps.spawnCircle(mousePosition);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && lockClick == true) {
                lockClick = false;
            }
        }

        ps.update(subStepRate);

        window.clear();

        for(const auto& ball : ps.getBalls())
        {
            window.draw(ball);
        }

        ui.updateSimulationDetails(deltaTime);

        window.draw(ps.getFrame());

        window.draw(sparks);

        window.display();
    }

    return 0;
}