#include "Entities/Spawner.h"

Spawner::Spawner(float radius) : ballRadius(radius) {}

Ball Spawner::spawnBall(const sf::Vector2f& position) {
    return Ball(position);
}