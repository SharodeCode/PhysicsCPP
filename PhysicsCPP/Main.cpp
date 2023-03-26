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
    Ball(sf::Vector2f position) : circleRadius(5.0f), velocity(0,0)
    {
        shape = sf::CircleShape(circleRadius);
        shape.setFillColor(sf::Color::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
        shape.setOrigin(sf::Vector2f(circleRadius, circleRadius));
        setPosition(position);
    }

    void update(float dt) {
        sf::Vector2f pos = getPosition();
        pos += velocity * dt;

        setPosition(pos);
    }

    void bounce(sf::Vector2f normal, float damping = 0.88f) {
        float dot = velocity.x * normal.x + velocity.y * normal.y;
        if (dot < 0) {
            velocity.x -= 2 * dot * normal.x * damping;
            velocity.y -= 2 * dot * normal.y * damping;
        }
    }

    void accelerate(sf::Vector2f a)
    {
        velocity += a;
    }

    float getRadius() const
    {
        return circleRadius;
    }

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(const sf::Vector2f& vel) { velocity = vel; }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(shape, states);
    }
};

void spawnCircle(std::vector<Ball>& balls, const sf::Vector2f& position) {
    balls.emplace_back(Ball(position));
}

void resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius) {
    sf::Vector2f delta = ball.getPosition() - center;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float ballRadius = ball.getRadius();

    if (distance >= 200.0f - ballRadius) {
        sf::Vector2f normal = delta / distance;

        ball.setVelocity(ball.getVelocity() - (0.8f * (ball.getVelocity().x * normal.x + ball.getVelocity().y * normal.y) * normal));
        ball.setVelocity(ball.getVelocity() * 0.99f);
        ball.setPosition(frame.getPosition() + normal * (200.0f - ballRadius));
    }

}

bool checkBallCollision(const Ball& a, const Ball& b) {
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    return distance <= a.getRadius() + b.getRadius();
}

void resolveBallCollision(Ball& a, Ball& b) {
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float overlap = a.getRadius() + b.getRadius() - distance;

    if (overlap > 0) {
        sf::Vector2f normal = delta / distance;
        a.move(overlap * normal * 0.5f);
        b.move(-overlap * normal * 0.5f);

        sf::Vector2f relativeVelocity = a.getVelocity() - b.getVelocity();
        float impulse = 0.8f * (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y);

        a.setVelocity(a.getVelocity() - impulse * normal);
        b.setVelocity(b.getVelocity() + impulse * normal);
    }
}

int main()
{
    initialise();

    // Set the gravity and bounce damping
    float damping = 0.85f;

    // Create a clock to control the movement
    sf::Clock clock = sf::Clock();

    float displayFramerateTime = 0.0f;
    float spawnCircleTime = 0.0f;

    std::vector<Ball> balls;

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
            spawnCircle(balls, sf::Vector2f(375, 185));
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
                spawnCircle(balls, mousePosition);
            }
        }

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && lockClick == true) {
                lockClick = false;
            }
        }

        for (auto& ball : balls) {
            ball.accelerate(sf::Vector2f(0.0f, 9.8f));
        }


        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                if (checkBallCollision(balls[i], balls[j])) {
                    resolveBallCollision(balls[i], balls[j]);
                }
            }
        }

        for (auto& ball : balls) {
            resolveHollowCircleCollision(ball, sf::Vector2f((window.getSize().x / 2), (window.getSize().y / 2)), 10.0f);

            ball.update(deltaTime);
        }

        window.clear();

        // Draw all the balls
        for(const auto& ball : balls)
        {
            window.draw(ball);
        }

        displayNumberOfObjects(balls.size());

        window.draw(frame);
        window.draw(textFPS);
        window.draw(textNumberOfObjects);
        window.display();
    }

    return 0;
}