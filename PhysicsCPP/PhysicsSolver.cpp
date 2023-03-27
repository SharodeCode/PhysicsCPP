#include "PhysicsSolver.h"


PhysicsSolver::PhysicsSolver() {

    // Create the frame (hollow circle)
    float frameRadius = 200.0f;
    frame = sf::CircleShape(frameRadius, 100);
    frame.setOutlineThickness(10.0f);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::White);
    frame.setOrigin(sf::Vector2(frameRadius, frameRadius));
    frame.setPosition(sf::Vector2f(400.0f, 250.0f));
}

void PhysicsSolver::spawnCircle(const sf::Vector2f& position) {
    balls.emplace_back(Ball(position));
}

void PhysicsSolver::update(float deltaTime)
{
    applyGravity();
    checkBallCollisions();
    checkFrameCollisions(deltaTime);
}

void PhysicsSolver::applyGravity() {
    for (auto& ball : balls) {
        ball.accelerate(sf::Vector2f(0.0f, 9.8f));
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
    float overlap = a.getRadius() + b.getRadius() - distance;

    float collision_distance = 2.0f * a.getRadius();

    if (distance <= collision_distance) {
        sf::Vector2f normal = delta / distance;
        sf::Vector2f relativeVelocity = a.getVelocity() - b.getVelocity();
        float impulse = 0.8f * (relativeVelocity.x * normal.x + relativeVelocity.y * normal.y);


        a.move(overlap * normal * 0.8f);
        b.move(-overlap * normal * 0.8f);

        a.setVelocity(a.getVelocity() - impulse * normal);
        b.setVelocity(b.getVelocity() + impulse * normal);
    }
}

void PhysicsSolver::checkFrameCollisions(float deltaTime) {

    for (auto& ball : balls) {
        resolveHollowCircleCollision(ball, sf::Vector2f((400.0f), (250.0f)), 10.0f);

        ball.update(deltaTime);
    }
}

void PhysicsSolver::checkBallCollisions() {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            resolveBallCollision(balls[i], balls[j]);
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