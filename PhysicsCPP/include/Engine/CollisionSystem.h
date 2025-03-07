#pragma once
#include "Entities/Ball.h"
#include <vector>

class CollisionSystem {
public:
    static void ResolveBallCollision(Ball& a, Ball& b);
    static void CheckBallCollisions(std::vector<Ball>& balls);
    static void ResolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius);
    static void checkBallCollisionsBruteForce(std::vector<Ball>& balls);
};
