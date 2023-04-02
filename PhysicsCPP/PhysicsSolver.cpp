#include "PhysicsSolver.h"
#include <future>
#include "ParticleSystem.h"

PhysicsSolver::PhysicsSolver(ParticleSystem* sparkss){

    // Create the frame (hollow circle)
    float frameRadius = 250.0f;
    frame = sf::CircleShape(frameRadius, 100);
    frame.setOutlineThickness(10.0f);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::White);
    frame.setOrigin(sf::Vector2(frameRadius, frameRadius));
    frame.setPosition(sf::Vector2f(400.0f, 400.0f));


    if (!buffer.loadFromFile("bouncyBall.wav")) {
    }

    sparks = sparkss;

    sound.setBuffer(buffer);
}

void PhysicsSolver::spawnCircle(const sf::Vector2f& position) {
    balls.emplace_back(Ball(position));
}

void PhysicsSolver::applyGravity() {
    for (auto& ball : balls) {
        ball.accelerate(sf::Vector2f(0.0f, ball.getGravity()));
    }
}

void PhysicsSolver::updateBalls(float dt)
{
    for (auto& ball : balls) {
        ball.update(dt);
        
    }
}

void PhysicsSolver::update(float subStepRate)
{
    std::vector<std::future<void>> futures;

    for (int i = 0; i < subSteps; i++) {
        futures.clear();

        applyGravity();

        futures.push_back(std::async(std::launch::async, &PhysicsSolver::checkBallCollisionsCollisionGrid, this));
        futures.push_back(std::async(std::launch::async, &PhysicsSolver::checkFrameCollisions, this));

        for (auto& future : futures) {
            future.wait();
        }

        updateBalls(subStepRate);
    }
}

void PhysicsSolver::resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius) {
    sf::Vector2f delta = ball.getPosition() - center;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float ballRadius = ball.getRadius();

    if (distance >= frame.getRadius() - ballRadius) {
        sf::Vector2f normal = delta / distance;

        ball.setVelocity(ball.getVelocity() - (0.8f * (ball.getVelocity().x * normal.x + ball.getVelocity().y * normal.y) * normal));
        ball.setVelocity(ball.getVelocity() * damping);

        ball.setPosition(frame.getPosition() + normal * (frame.getRadius() - ballRadius));
    }
}

void PhysicsSolver::resolveBallCollision(Ball& a, Ball& b) {
    
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float collision_distance = a.getRadius() + b.getRadius();

    
    if (distance <= collision_distance) {
        sf::Vector2f normal = delta / distance;
        sf::Vector2f relative_velocity = (a.getPosition() - a.position_last) - (b.getPosition() - b.position_last);
        float impulse = 2.0f * (relative_velocity.x * normal.x + relative_velocity.y * normal.y);


        if (impulse < -3.5f || impulse > 3.5f) {

            sound.play();

            // Calculate the collision point
            sf::Vector2f collisionPoint = a.getPosition() + normal * (a.getRadius() - collision_distance);

            // Set the particle system emitter to the collision point and add sparks
            sparks->setEmitter(collisionPoint);
            sparks->addParticles(10);
        }

        const float delta = 0.65f * (distance - collision_distance);

        a.move(- ((normal * delta * b.radius) / (a.radius + b.radius)));
        b.move((normal * delta * a.radius) / (a.radius + b.radius));

    }
}

void PhysicsSolver::checkFrameCollisions() {

    for (auto& ball : balls) {
        resolveHollowCircleCollision(ball, frame.getPosition(), frame.getRadius());
    }
}

void PhysicsSolver::checkBallCollisionsBruteForce() {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            resolveBallCollision(balls[i], balls[j]);
        }
    }
}

void PhysicsSolver::checkBallCollisionsCollisionGrid() {

    float CELL_SIZE = 40.0f;

    // Create the grid
    int gridWidth = static_cast<int>(std::ceil(800.0f / CELL_SIZE));
    int gridHeight = static_cast<int>(std::ceil(800.0f / CELL_SIZE));

    std::vector<std::vector<std::vector<Ball*>>> grid(gridWidth, std::vector<std::vector<Ball*>>(gridHeight));

    // Assign balls to grid cells
    for (auto& ball : balls) {
        int x = static_cast<int>(ball.getPosition().x / CELL_SIZE);
        int y = static_cast<int>(ball.getPosition().y / CELL_SIZE);

        grid[x][y].push_back(&ball);
    }

    // Check for collisions within the same cell and neighboring cells
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                        for (auto& ballA : grid[x][y]) {
                            for (auto& ballB : grid[nx][ny]) {
                                if (ballA != ballB) {

                                    resolveBallCollision(*ballA, *ballB);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}


const std::vector<Ball>& PhysicsSolver::getBalls() const
{
    return balls;
}

const sf::CircleShape& PhysicsSolver::getFrame() const
{
    return frame;
}