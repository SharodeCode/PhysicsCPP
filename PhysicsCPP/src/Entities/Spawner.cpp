#include "Entities/Spawner.h"

Spawner::Spawner(float radius) : ballRadius(radius) {}

Ball Spawner::spawnBall(const sf::Vector2f& position) {

    Ball newBall = Ball(position);
	newBall.setVelocity(sf::Vector2f(0.0f, 50.0f));
    return newBall;
}