#include "Entities/Spawner.h"

Spawner::Spawner(float radius)
    : ballRadius(radius) {}

std::unique_ptr<Ball> Spawner::spawnBall(const sf::Vector2f& position, PhysicsDataPool* pool, int index) {
    return std::make_unique<Ball>(position, pool, index);
}
