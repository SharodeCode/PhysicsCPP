#include "Engine/CollisionSystem.h"
#include <iostream>

int CollisionSystem::collisionChecks = 0;
int CollisionSystem::collisionsResolved = 0;
int CollisionSystem::gridWidth = 0;
int CollisionSystem::gridHeight = 0;

std::vector<std::vector<int>> CollisionSystem::spatialGridFlat;

void CollisionSystem::resolveBallCollision(FlatBallData& a, FlatBallData& b) {

    // Calculate the vector between a and b and their squared distance
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    float distSq = dx * dx + dy * dy;

    // Minimum distance before 2 balls are considered colliding
    float minDist = a.radius + b.radius;

    // Prevent division by zero when balls are on top of each other and only proceed if balls are overlapping
    if (distSq < 0.0001f || distSq >= minDist * minDist)
        return;

    // Calculate the normal vector and overlap
    float dist = std::sqrt(distSq);
    float overlap = minDist - dist + 0.01f; // Add bias to ensure separation
    float nx = dx / dist;
    float ny = dy / dist;

    // Push both objects apart equally along the collision normal
    float percent = 0.5f; // Equal push
    float pushX = nx * overlap * percent;
    float pushY = ny * overlap * percent;

    a.x += pushX;
    a.y += pushY;
    b.x -= pushX;
    b.y -= pushY;

    // Dampen velocity by adjusting last position
    const float damping = 0.98f;  // 1 = no damping, <1 = dampen motion
    float ax = a.x - a.lastX;
    float ay = a.y - a.lastY;
    float bx = b.x - b.lastX;
    float by = b.y - b.lastY;

    a.lastX = a.x - ax * damping;
    a.lastY = a.y - ay * damping;
    b.lastX = b.x - bx * damping;
    b.lastY = b.y - by * damping;
}

void CollisionSystem::checkBallCollisions(PhysicsDataPool& pool) {

    // Setup spatial grid
    const float CELL_SIZE = GameConfig::BALL_RADIUS * 4.0f;
    gridWidth = static_cast<int>(std::ceil(GameConfig::WINDOW_WIDTH / CELL_SIZE));
    gridHeight = static_cast<int>(std::ceil(GameConfig::WINDOW_HEIGHT / CELL_SIZE));

    // First-time setup or window resize only if needed
    if (spatialGridFlat.size() != gridWidth * gridHeight) {
        spatialGridFlat = std::vector<std::vector<int>>(gridWidth * gridHeight);
    }
    else {
        // If reusing grid, clear contents.
        for (auto& cell : spatialGridFlat) cell.clear();
    }

    // Assign balls to grid cells
    for (int i = 0; i < pool.ballData.size(); ++i) {
        const auto& ball = pool.get(i);
        
        // Clamped to stop calculations of balls that are offscreen.
        int x = std::clamp(static_cast<int>(ball.x / CELL_SIZE), 0, gridWidth - 1);
        int y = std::clamp(static_cast<int>(ball.y / CELL_SIZE), 0, gridHeight - 1);
        spatialGridFlat[FLAT_INDEX(x, y)].push_back(i);
    }

    // Loop over every cell in the spatial grid
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {

            for (int dx = -1; dx <= 1; ++dx) {
                for (int dy = -1; dy <= 1; ++dy) {
                    int nx = x + dx; // Neighbor cell X
                    int ny = y + dy; // Neighbor cell Y

                    // Skip out-of-bounds neighbors
                    if (nx < 0 || ny < 0 || nx >= gridWidth || ny >= gridHeight) continue;

                    const auto& cellA = spatialGridFlat[FLAT_INDEX(x, y)];
                    const auto& cellB = spatialGridFlat[FLAT_INDEX(nx, ny)];

                    // Loop over all balls in the current cell
                    for (int idxA : cellA) {
                        // Loop over all balls in the neighbor cell
                        for (int idxB : cellB) {
							if (idxA >= idxB) continue; // Skip self-collision and double processing, each pair only processed once.
                            
                            ++collisionChecks;
                            resolveBallCollision(pool.get(idxA), pool.get(idxB)); // Check and resolve potential collision
                        }
                    }
                }
            }
        }
    }

}


void CollisionSystem::resolveHollowCircleCollision(PhysicsDataPool& pool, int physicsIndex, float boundaryRadius, const sf::Vector2f& boundaryCenter) {
    FlatBallData& data = pool.get(physicsIndex);
    sf::Vector2f pos(data.x, data.y);
    sf::Vector2f delta = pos - boundaryCenter;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float maxDist = boundaryRadius - data.radius;

    if (distance > maxDist) {
        sf::Vector2f normal = delta / distance;
        float overlap = distance - maxDist;

        // Push inward along the normal
        data.x -= normal.x * overlap;
        data.y -= normal.y * overlap;

        // Dampen motion
        float dx = data.x - data.lastX;
        float dy = data.y - data.lastY;
        float damping = 0.98f;
        data.lastX = data.x - dx * damping;
        data.lastY = data.y - dy * damping;
    }


}

void CollisionSystem::resolveBoxWallCollisions(RigidbodyComponent& rb, const std::vector<std::shared_ptr<BoundaryWall>>& staticWalls) {
    auto* pool = rb.getPool();
    int idx = rb.getIndex();
    auto& data = pool->get(idx);

    float radius = data.radius;
    float newX = data.x;
    float newY = data.y;

    for (const auto& wall : staticWalls) {
        auto renderer = wall->getComponent<RendererComponent>().lock();
        if (!renderer) continue;

        sf::Vector2f wallPos = wall->getPosition();
        sf::Vector2f wallSize = renderer->getSize();
        sf::Vector2f half = wallSize / 2.f;

        float clampedX = std::clamp(newX, wallPos.x - half.x, wallPos.x + half.x);
        float clampedY = std::clamp(newY, wallPos.y - half.y, wallPos.y + half.y);

        float dx = newX - clampedX;
        float dy = newY - clampedY;
        float distSq = dx * dx + dy * dy;

        if (distSq < radius * radius) {
            float dist = std::sqrt(distSq);
            float nx = (dist > 0.001f) ? dx / dist : 0.f;
            float ny = (dist > 0.001f) ? dy / dist : -1.f;
            float penetration = radius - dist;

            // Push out
            data.x += nx * penetration;
            data.y += ny * penetration;

            // Dampen motion
            float velX = data.x - data.lastX;
            float velY = data.y - data.lastY;
            float damping = GameConfig::ELASTICITY;

            data.lastX = data.x - velX * damping;
            data.lastY = data.y - velY * damping;
        }
    }

}

void CollisionSystem::checkBallCollisionsBruteForce(std::vector<Ball>& balls) {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            //resolveBallCollision(balls[i], balls[j]);
        }
    }
}