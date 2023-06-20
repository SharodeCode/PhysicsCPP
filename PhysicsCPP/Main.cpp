#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "PhysicsSolver.h"
#include "UI.h"
#include "Portal.h"
#include "ParticleSystem.h"

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

    sf::Texture texture;
    if (!texture.loadFromFile("./images/portal.png"))
    {
        // error...
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);

    Portal test(&ps, &sprite);

    Button::buttonType currentButton = Button::buttonType::mute;

    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();

        accumulator += deltaTime;

        sparks.update(elapsed);
        test.update(deltaTime);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && lockClick == false) {
                if (currentButton == Button::buttonType::clickToSpawn) {
                    lockClick = true;
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    ps.spawnCircle(mousePosition);
                }
                else if (currentButton == Button::buttonType::ballSpawner) {
                    test.addPortal(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
                }

                if (ui.isButtonClicked()) {
                    currentButton = ui.buttonClicked();
                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left && lockClick == true) {
                    lockClick = false;
                }
            }
        }



        ps.update(subStepRate);

        window.clear();

        test.drawPortals(&window);
        window.draw(sprite);

        for(const auto& ball : ps.getBalls())
        {
            window.draw(ball);
        }

        ui.updateUI(deltaTime);

        window.draw(ps.getFrame());

        window.draw(sparks);

        window.display();
    }

    return 0;
}