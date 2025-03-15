#include "Entities/Spawner.h"

Spawner::Spawner(float radius)
    : ballRadius(radius) {}

std::unique_ptr<Ball> Spawner::spawnBall(const sf::Vector2f& position) {
    auto newBall = std::make_unique<Ball>(position);
    newBall->setVelocity(sf::Vector2f(0.0f, 50.0f));

    return newBall;
}
