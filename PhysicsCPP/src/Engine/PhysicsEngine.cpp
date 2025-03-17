#include "Engine/PhysicsEngine.h"
#include "Engine/CollisionSystem.h"
#include <future>
#include <PhysicsConstants.h>

PhysicsEngine::PhysicsEngine()
    : boundary(250.0f, sf::Vector2f(400.0f, 400.0f)), spawner(10.0f) {}

void PhysicsEngine::spawnBall(const sf::Vector2f& position) {
    balls.push_back(spawner.spawnBall(position));
}

void PhysicsEngine::addPortal(const sf::Vector2f& position, const sf::Texture& texture) {
    portals.push_back(Portal(position, texture, balls));
}

void PhysicsEngine::applyGravity() {
    for (auto& ball : balls) {
        ball->resetForces(); // Reset before applying new forces
		ball->accelerate(sf::Vector2f(0.0f, GRAVITY));
    }
}


void PhysicsEngine::updateBalls(float dt)
{
    for (auto& ball : balls) {
        ball->update(dt);
    }
}

void PhysicsEngine::update(float subStepRate) {
    std::vector<std::future<void>> futures;

    for (int i = 0; i < subStepCount; i++) {
        futures.clear();

        applyGravity();

        futures.push_back(std::async(std::launch::async, &CollisionSystem::checkBallCollisions, std::ref(balls)));
        futures.push_back(std::async(std::launch::async, [this]() {
            for (auto& ball : balls) {
                CollisionSystem::resolveHollowCircleCollision(*ball, boundary.getPosition(), boundary.getRadius());
            }
        }));

        for (auto& future : futures) {
            future.wait();
        }

        updateBalls(subStepRate);
    }

    for (auto& portal : portals) {
        portal.update(subStepRate);
    }
}

const std::vector<std::unique_ptr<Ball>>& PhysicsEngine::getBalls() const
{
    return balls;
}

const std::vector<Portal>& PhysicsEngine::getPortals() const
{
    return portals;
}

const sf::CircleShape& PhysicsEngine::getBoundaryShape() const
{
    return boundary.getFrame();
}

void PhysicsEngine::toggleAudioActive() {
    audioActive = !audioActive;
}