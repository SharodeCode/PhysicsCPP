#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "PhysicsSolver.h"

const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 800;

static sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");

static sf::Text textFPS;
static sf::Text textNumberOfObjects;
static sf::Font font;

static void displayFPS(float fps)
{
    textFPS.setString("FPS: " + std::to_string(fps));
}

static void displayNumberOfObjects(int numberOfObjects)
{
    textNumberOfObjects.setString("Number of objects: " + std::to_string(numberOfObjects));
}

static void initialise() {

    // Initialise font and text
    font.loadFromFile("Roboto.ttf");
    textFPS.setFont(font);
    textFPS.setCharacterSize(10);
    textFPS.setFillColor(sf::Color::White);
    textFPS.setStyle(sf::Text::Regular);

    textNumberOfObjects.setFont(font);
    textNumberOfObjects.setCharacterSize(10);
    textNumberOfObjects.setFillColor(sf::Color::White);
    textNumberOfObjects.setStyle(sf::Text::Regular);
    textNumberOfObjects.setPosition(sf::Vector2f(0, textFPS.getLocalBounds().height + 12));
}

int main()
{
    initialise();

    window.setFramerateLimit(600);

    PhysicsSolver ps = PhysicsSolver();

    // Set the gravity and bounce damping
    float damping = 0.85f;

    // Create a clock to control the movement
    sf::Clock clock = sf::Clock();

    float displayFramerateTime = 0.0f;
    float spawnCircleTime = 0.0f;

    static bool lockClick = false;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        float fps = 1.0f / (deltaTime);

        displayFramerateTime += deltaTime;
        spawnCircleTime += deltaTime;

        if (displayFramerateTime > 0.5)
        {
            displayFPS(fps);
            displayFramerateTime = 0;
        }

        if (spawnCircleTime > 0.1)
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

        ps.update(deltaTime);


        window.clear();

        // Draw all the balls
        for(const auto& ball : ps.getBalls())
        {
            window.draw(ball);
        }

        displayNumberOfObjects(ps.getBalls().size());

        window.draw(ps.getFrame());
        window.draw(textFPS);
        window.draw(textNumberOfObjects);
        window.display();
    }

    return 0;
}