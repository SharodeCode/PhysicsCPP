#pragma once
#include <vector>
#include <cmath>
#include "GameConfig.h"
#include "Entities/Ball.h"
#include "Entities/BaseEntity.h"
#include "Entities/BoundaryWall.h"

class CollisionSystem {
private:
    static int gridWidth;
    static int gridHeight;

public:

    #define FLAT_INDEX(x, y) ((y) * CollisionSystem::gridWidth + (x))

    // Benchmark
    static int collisionChecks;
    static int collisionsResolved;

    static std::vector<std::vector<int>> spatialGridFlat;

    static void checkBallCollisions(PhysicsDataPool& pool);
    static void resolveHollowCircleCollision(PhysicsDataPool& pool, int physicsIndex, float boundaryRadius, const sf::Vector2f& boundaryCenter);
    static void resolveBoxWallCollisions(RigidbodyComponent& rb, const std::vector<std::shared_ptr<BoundaryWall>>& staticWalls);
    static void checkBallCollisionsBruteForce(std::vector<Ball>& balls);
    static void resolveBallCollision(FlatBallData& a, FlatBallData& b);
};
