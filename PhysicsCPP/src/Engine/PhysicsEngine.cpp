#include "Engine/PhysicsEngine.h"
#include "Engine/CollisionSystem.h"
#include <future>

PhysicsEngine::PhysicsEngine() : boundary(250.0f, sf::Vector2f(400.0f, 400.0f)) {

}

void PhysicsEngine::spawnCircle(const sf::Vector2f& position) {
    balls.emplace_back(Ball(position));
}

void PhysicsEngine::applyGravity() {
    for (auto& ball : balls) {
        RigidbodyComponent* rb = ball.GetRigidbody();
        if (rb) {
            rb->ApplyForce(sf::Vector2f(0.0f, rb->mass * ball.getGravity()));
        }
    }
}


void PhysicsEngine::updateBalls(float dt)
{
    for (auto& ball : balls) {
        ball.update(dt);

    }
}

void PhysicsEngine::update(float subStepRate) {
    std::vector<std::future<void>> futures;

    for (int i = 0; i < subSteps; i++) {
        futures.clear();

        applyGravity();

        futures.push_back(std::async(std::launch::async, &CollisionSystem::CheckBallCollisions, std::ref(balls)));
        futures.push_back(std::async(std::launch::async, [this]() {
            for (auto& ball : balls) {
                CollisionSystem::ResolveHollowCircleCollision(ball, boundary.getPosition(), boundary.getRadius());
            }
        }));

        for (auto& future : futures) {
            future.wait();
        }

        updateBalls(subStepRate);
    }
}

const std::vector<Ball>& PhysicsEngine::getBalls() const
{
    return balls;
}

const sf::CircleShape& PhysicsEngine::getFrame() const
{
    return boundary.getFrame();
}

void PhysicsEngine::toggleAudioActive() {
    audioActive = !audioActive;
}