#include <SFML/Graphics.hpp>

const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 800;

static sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
sf::CircleShape frame;

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

    // Create the frame (hollow circle)
    float frameRadius = 200.0f;
    frame = sf::CircleShape(frameRadius, 100);
    frame.setOutlineThickness(10.0f);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::White);
    frame.setOrigin(sf::Vector2(frameRadius, frameRadius));
    frame.setPosition(sf::Vector2f((window.getSize().x / 2), (window.getSize().y / 2)));

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

class Ball : public sf::Drawable, public sf::Transformable
{
    sf::Vector2f velocity;
    sf::CircleShape shape;

    const float gravity = 9.8f * 150;
    float circleRadius = 5.0f;

public:
    Ball(sf::Vector2f position) : circleRadius(15.0f), velocity(0,0)
    {
        shape = sf::CircleShape(circleRadius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(sf::Vector2f(circleRadius, circleRadius));
        shape.setPosition(sf::Vector2f(position.x, position.y));
    }

    void update(float dt) {
        sf::Vector2f pos = getPosition();
        pos += velocity * dt;

        setPosition(pos);
        velocity.y += gravity * dt;
    }

    sf::Vector2f getPosition()
    {
        return shape.getPosition();
    }

    void setPosition(sf::Vector2f position)
    {
        shape.setPosition(position);
    }

    float getRadius()
    {
        return circleRadius;
    }
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(shape, states);
    }
};

void spawnCircle(std::vector<Ball>& balls, const sf::Vector2f& position) {
    balls.emplace_back(position);
}

int main()
{
    initialise();

    // Set the gravity and bounce damping
    float gravity = 800.0f;
    float damping = 0.85f;

    // Create a clock to control the movement
    sf::Clock clock = sf::Clock();

    float displayFramerateTime = 0.0f;

    std::vector<Ball> balls = {
        Ball(sf::Vector2f(375, 185)),
    };

    static bool lockClick = false;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        float fps = 1.0f / (deltaTime);

        displayFramerateTime += deltaTime;
        if (displayFramerateTime > 0.5)
        {
            displayFPS(fps);
            displayFramerateTime = 0;
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
                spawnCircle(balls, mousePosition);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && lockClick == true) {
                lockClick = false;
            }
        }

        for (auto& ball : balls) {
            ball.update(deltaTime);
        }

        window.clear();

        // Draw all the balls
        for(const auto& circle : balls)
        {
            window.draw(circle);
        }

        displayNumberOfObjects(balls.size());

        window.draw(frame);
        window.draw(textFPS);
        window.draw(textNumberOfObjects);
        window.display();
    }

    return 0;
}