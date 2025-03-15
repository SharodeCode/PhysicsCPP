#pragma once
#include "Entities/Ball.h"

class Spawner {
private:
    float ballRadius;

public:
    Spawner(float radius);

    std::unique_ptr<Ball> spawnBall(const sf::Vector2f& position);
};
