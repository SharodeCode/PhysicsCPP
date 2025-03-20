#pragma once
#include <vector>
#include <cmath>
#include "GameConfig.h"
#include "Entities/Ball.h"
#include "Entities/BaseEntity.h"

class CollisionSystem {
public:
    static void resolveBallCollision(RigidbodyComponent& a, RigidbodyComponent& b);
    static void checkBallCollisions(std::vector<std::shared_ptr<RigidbodyComponent>>& balls);
    static void resolveHollowCircleCollision(std::shared_ptr<RigidbodyComponent>& ball, const sf::Vector2f& center, float outerRadius);
    static void checkBallCollisionsBruteForce(std::vector<Ball>& balls);
};
