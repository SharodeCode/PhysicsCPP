#include "Engine/CollisionSystem.h"
#include <iostream>

std::vector<std::vector<std::vector<RigidbodyComponent*>>> CollisionSystem::spatialGrid;
int CollisionSystem::gridWidth = 0;
int CollisionSystem::gridHeight = 0;

void CollisionSystem::resolveBallCollision(RigidbodyComponent& a, RigidbodyComponent& b) {

	// Calculate the vector between a and b and their distance
    sf::Vector2f delta = a.getOwner()->getPosition() - b.getOwner()->getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    // Minimum distance before 2 balls are considered colliding
    float collision_distance = a.getRadius() + b.getRadius();

	// Prevent division by zero when balls are on top of each other
    if (distance < .01f)
        distance = .01f;

    // Only proceed if balls are overlapping
    if (distance < collision_distance) {
		// Calculate the normal vector between the two balls. And the overlap.
        sf::Vector2f normal = delta / distance;
        float overlap = collision_distance - distance;

        // Push both objects apart equally along the collision normal.
        float percent = 0.5f; // 0.5 for equal displacement
        sf::Vector2f correction = normal * (overlap * percent);
        a.getOwner()->setPosition(a.getOwner()->getPosition() + correction);
        b.getOwner()->setPosition(b.getOwner()->getPosition() - correction);

		// Compute velocity based on previous position
        sf::Vector2f aVel = a.getOwner()->getPosition() - a.getOwner()->getPositionLast();
        sf::Vector2f bVel = b.getOwner()->getPosition() - b.getOwner()->getPositionLast();
        sf::Vector2f relVel = aVel - bVel;
        float relNormal = relVel.x * normal.x + relVel.y * normal.y;

		// Apply a bound, only resolve if balls are moving towards each other
        if (relNormal < 0.f) {
            float bounce = 0.05f; // 0 = no bounce, 1 = full bounce
            sf::Vector2f impulse = normal * (-relNormal * bounce);

            a.getOwner()->setPositionLast(a.getOwner()->getPositionLast() - impulse * 0.5f);
            b.getOwner()->setPositionLast(b.getOwner()->getPositionLast() + impulse * 0.5f);
        }

    }
}

void CollisionSystem::checkBallCollisions(std::vector<std::shared_ptr<RigidbodyComponent>>& balls) {

    // Setup spatial grid
    const float CELL_SIZE = GameConfig::BALL_RADIUS * 4.0f;
    gridWidth = static_cast<int>(std::ceil(GameConfig::WINDOW_WIDTH / CELL_SIZE));
    gridHeight = static_cast<int>(std::ceil(GameConfig::WINDOW_HEIGHT / CELL_SIZE));

    // First-time setup or window resize only if needed
    if (spatialGrid.size() != gridWidth || spatialGrid[0].size() != gridHeight) {
        spatialGrid = std::vector<std::vector<std::vector<RigidbodyComponent*>>>(
            gridWidth, std::vector<std::vector<RigidbodyComponent*>>(gridHeight)
        );
    }
    else {
        // If no new grid needed, reuse existing grid structure, clear contents
        for (int x = 0; x < gridWidth; ++x)
            for (int y = 0; y < gridHeight; ++y)
                spatialGrid[x][y].clear();
    }

    // Assign balls to grid cells
    for (auto& ball : balls) {
		// Clamped to stop calculations of balls that are offscreen.
        int x = std::clamp(static_cast<int>(ball->getOwner()->getPosition().x / CELL_SIZE), 0, gridWidth - 1);
        int y = std::clamp(static_cast<int>(ball->getOwner()->getPosition().y / CELL_SIZE), 0, gridHeight - 1);

        spatialGrid[x][y].push_back(ball.get());
    }
    int colCount = 0;

    // Loop over every cell in the spatial grid
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {

            // Loop over neighboring cell offsets (-1, 0, 1) in both directions
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {

                    int nx = x + i; // Neighbor cell X
                    int ny = y + j; // Neighbor cell Y

                    // Skip out-of-bounds neighbors
                    if (nx < 0 || ny < 0 || nx >= gridWidth || ny >= gridHeight) continue;

                    // Loop over all balls in the current cell
                    for (auto* ballA : spatialGrid[x][y]) {

                        // Loop over all balls in the neighbor cell
                        for (auto* ballB : spatialGrid[nx][ny]) {

                            if (ballA == ballB) continue; // Skip self-collision

                            // Prevent double processing, each pair only processed once.
                            if (ballA < ballB) {
								++colCount;
                                resolveBallCollision(*ballA, *ballB); // Check and resolve potential collision
                            }
                        }
                    }
                }
            }

        }
    }
    std::cout << "Collisions this frame: " << colCount << "\n";
    colCount = 0;
}

void CollisionSystem::resolveHollowCircleCollision(std::shared_ptr<RigidbodyComponent>& ball, const sf::Vector2f& boundaryPosition, float boundaryRadius) {
    sf::Vector2f delta = ball->getOwner()->getPosition() - boundaryPosition;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float ballRadius = ball->getRadius();

    if (distance > boundaryRadius - ballRadius) {
        sf::Vector2f normal = delta / distance;

        // Reflect motion
        sf::Vector2f vel = ball->getOwner()->getPosition() - ball->getOwner()->getPositionLast();
        float relNormal = vel.x * normal.x + vel.y * normal.y;

        if (relNormal > 0.f) {
            float elasticity = 0.02f;
            sf::Vector2f impulse = normal * (-relNormal * elasticity);
            ball->getOwner()->setPositionLast(ball->getOwner()->getPositionLast() - impulse);
        }

        // Clamp inside
        ball->getOwner()->setPosition(boundaryPosition + normal * (boundaryRadius - ballRadius));
    }

}

void CollisionSystem::checkBallCollisionsBruteForce(std::vector<Ball>& balls) {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            //resolveBallCollision(balls[i], balls[j]);
        }
    }
}