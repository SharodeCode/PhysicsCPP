#include "Engine/CollisionSystem.h"
#include <iostream>
#include <array>

int CollisionSystem::collisionChecks = 0;
int CollisionSystem::collisionsResolved = 0;
int CollisionSystem::gridWidth = 0;
int CollisionSystem::gridHeight = 0;

std::vector<size_t> CollisionSystem::cellOffsets;
std::vector<int> CollisionSystem::flatGridEntries;

static constexpr std::array<int[2], 6> neighborOffsets = {{
    {0, 0}, {1, 0}, {0, 1}, {1, 1}, {-1, 1}, {-1, 0}
} };

void CollisionSystem::resolveBallCollision(FlatBallData& a, FlatBallData& b, float dx, float dy, float distSq) {

    // Minimum distance before 2 balls are considered colliding
    float minDist = a.radius + b.radius;

    // Prevent division by zero when balls are on top of each other and only proceed if balls are overlapping
    if (distSq < 0.0001f || distSq >= minDist * minDist)
        return;

    collisionsResolved++;

    // Compute actual distance and collision normal
    float dist = std::sqrt(distSq);
    float overlap = minDist - dist + 0.01f; // Add bias to ensure separation
    float nx = dx / dist;
    float ny = dy / dist;

    // Push both objects apart equally
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

	// Calculate grid dimensions based on cell size
    const float CELL_SIZE = GameConfig::BALL_RADIUS * 4.0f;
    gridWidth = static_cast<int>(std::ceil(GameConfig::WINDOW_WIDTH / CELL_SIZE));
    gridHeight = static_cast<int>(std::ceil(GameConfig::WINDOW_HEIGHT / CELL_SIZE));

    // First-time setup or window resize only if needed
    if (cellOffsets.size() != gridWidth * gridHeight + 1) {
        cellOffsets.resize(gridWidth * gridHeight + 1);
        flatGridEntries.reserve(pool.ballData.size());  // One-time preallocation
    }
    flatGridEntries.clear();  // Reuse allocation

    // Temporary flat-grid count per cell
    std::vector<size_t> cellCounts(gridWidth * gridHeight, 0);

    // Count entries per cell
    for (int i = 0; i < pool.ballData.size(); ++i) {
        const auto& ball = pool.get(i);
		// Determine cell index
        int x = std::clamp(static_cast<int>(ball.x / CELL_SIZE), 0, gridWidth - 1);
        int y = std::clamp(static_cast<int>(ball.y / CELL_SIZE), 0, gridHeight - 1);
        ++cellCounts[FLAT_INDEX(x, y)];
    }

    // Compute cellOffsets from counts
    size_t offset = 0;
    for (size_t i = 0; i < cellCounts.size(); ++i) {
        cellOffsets[i] = offset;
        offset += cellCounts[i];
    }
    cellOffsets[gridWidth * gridHeight] = offset;
    flatGridEntries.resize(offset);

    // fill flatGridEntries
    std::fill(cellCounts.begin(), cellCounts.end(), 0);

    // Assign balls to grid cells
    for (int i = 0; i < pool.ballData.size(); ++i) {
        const auto& ball = pool.get(i);

        int x = std::clamp(static_cast<int>(ball.x / CELL_SIZE), 0, gridWidth - 1);
        int y = std::clamp(static_cast<int>(ball.y / CELL_SIZE), 0, gridHeight - 1);
        int cellIndex = FLAT_INDEX(x, y);

        size_t insertPos = cellOffsets[cellIndex] + cellCounts[cellIndex]++;
        flatGridEntries[insertPos] = i;
    }

    // Loop over every cell in the spatial grid
    unsigned int stripeCount = 1; // For now, single-threaded
    for (int stripe = 0; stripe < static_cast<int>(stripeCount); ++stripe) {
        runCollisionStripe(pool, stripe, stripeCount);
    }
}

void CollisionSystem::runCollisionStripe(PhysicsDataPool& pool, int stripe, int stripeCount) {

    // Loop over every X column in this stripe
    for (int x = stripe; x < gridWidth; x += stripeCount) {
        for (int y = 0; y < gridHeight; ++y) {

            // Get flattened index for cell (x, y)
            int indexA = FLAT_INDEX(x, y);
            size_t startA = cellOffsets[indexA];
            size_t endA = cellOffsets[indexA + 1];

            // Skip empty cells
            if (startA == endA) continue;

            // Check against this cell and its relevant neighbors
            for (const auto& offset : neighborOffsets) {
                int dx = offset[0];
                int dy = offset[1];
                int nx = x + dx; // Neighbor cell X
                int ny = y + dy; // Neighbor cell Y

                // Skip out-of-bounds neighbors
                if (nx < 0 || ny < 0 || nx >= gridWidth || ny >= gridHeight) continue;

                int indexB = FLAT_INDEX(nx, ny);
                size_t startB = cellOffsets[indexB];
                size_t endB = cellOffsets[indexB + 1];

                // Skip if neighbor cell is also empty
                if (startB == endB) continue;

                // Avoid redundant comparisons in the same cell
                bool sameCell = (indexA == indexB);

                // Loop over all balls in the current cell
                for (size_t i = startA; i < endA; ++i) {
                    int idxA = flatGridEntries[i];

                    // Loop over all balls in the neighbor cell
                    for (size_t j = startB; j < endB; ++j) {

                        int idxB = flatGridEntries[j];

                        // Skip self-collision and double processing.
                        if (sameCell && idxA >= idxB) continue;

                        ++collisionChecks;

                        auto& a = pool.get(idxA);
                        auto& b = pool.get(idxB);

                        // Calculate the vector between a and b and their squared distance
						// Perform AABB check to avoid expensive sqrt
                        float maxDist = a.radius + b.radius;
                        float dx = std::abs(a.x - b.x);
                        float dy = std::abs(a.y - b.y);
                        float distSq = dx * dx + dy * dy;
                        if (distSq >= maxDist * maxDist) continue;

                        resolveBallCollision(a, b, dx, dy, distSq);
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