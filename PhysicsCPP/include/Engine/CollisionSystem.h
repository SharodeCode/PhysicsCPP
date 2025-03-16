#pragma once
#include "Entities/Ball.h"
#include <vector>

class CollisionSystem {
public:
    static void resolveBallCollision(Ball& a, Ball& b);
    static void checkBallCollisions(std::vector<std::unique_ptr<Ball>>& balls);
    static void resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius);
    static void checkBallCollisionsBruteForce(std::vector<Ball>& balls);
};
