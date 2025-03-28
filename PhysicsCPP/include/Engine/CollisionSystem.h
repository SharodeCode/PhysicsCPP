#pragma once
#include <vector>
#include <cmath>
#include "GameConfig.h"
#include "Entities/Ball.h"
#include "Entities/BaseEntity.h"
#include "Entities/BoundaryWall.h"

class CollisionSystem {
private:
    static std::vector<std::vector<std::vector<RigidbodyComponent*>>> spatialGrid;
    static int gridWidth;
    static int gridHeight;

public:
    // Benchmark
    static int collisionChecks;
    static int collisionsResolved;

    static void resolveBallCollision(RigidbodyComponent& a, RigidbodyComponent& b);
    static void checkBallCollisions(std::vector<std::shared_ptr<RigidbodyComponent>>& balls);
    static void resolveHollowCircleCollision(std::shared_ptr<RigidbodyComponent>& ball, const sf::Vector2f& center, float outerRadius);
    static void resolveBoxWallCollisions(std::shared_ptr<RigidbodyComponent>& ball, const std::vector<std::shared_ptr<BoundaryWall>>& staticWalls);
    static void checkBallCollisionsBruteForce(std::vector<Ball>& balls);
};
