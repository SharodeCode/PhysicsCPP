#include "Engine/CollisionSystem.h"


void CollisionSystem::resolveBallCollision(RigidbodyComponent& a, RigidbodyComponent& b) {
    sf::Vector2f delta = a.getOwner()->getPosition() - b.getOwner()->getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float collision_distance = a.getRadius() + b.getRadius();

    if (distance < collision_distance) {
        sf::Vector2f normal = delta / distance; // Collision normal
        sf::Vector2f relative_velocity = a.getVelocity() - b.getVelocity();

        // Ensure objects move apart by computing impulse correctly
        float elasticity = 0.9f;  // 90% elasticity for bounce
        float impulse = (-(1 + elasticity) * (relative_velocity.x * normal.x + relative_velocity.y * normal.y)) /
            ((1 / a.getMass()) + (1 / b.getMass()));

        sf::Vector2f impulseVector = impulse * normal;

        // Apply impulse to change velocity, preventing sticking
        a.applyVelocity(a.getVelocity() + (impulseVector / a.getMass()));
        b.applyVelocity(b.getVelocity() - (impulseVector / b.getMass()));

        // Push objects apart to prevent overlap
        float pushFactor = 0.5f; // Ensures equal separation
        const float deltaMove = 0.65f * (distance - collision_distance);
        a.move(-(normal * deltaMove * pushFactor));
        b.move(normal * deltaMove * pushFactor);
    }
}


void CollisionSystem::checkBallCollisions(std::vector<std::shared_ptr<RigidbodyComponent>>& balls) {

    float CELL_GRID_SIZE = 40.0f;

    // Create the grid
    int gridWidth = static_cast<int>(std::ceil(GameConfig::WINDOW_WIDTH / CELL_GRID_SIZE));
    int gridHeight = static_cast<int>(std::ceil(GameConfig::WINDOW_HEIGHT / CELL_GRID_SIZE));

    std::vector<std::vector<std::vector<RigidbodyComponent*>>> grid(gridWidth, std::vector<std::vector<RigidbodyComponent*>>(gridHeight));

    // Assign balls to grid cells
    for (auto& rb : balls) {
        int x = static_cast<int>(rb->getOwner()->getPosition().x / CELL_GRID_SIZE);
        int y = static_cast<int>(rb->getOwner()->getPosition().y / CELL_GRID_SIZE);

        grid[x][y].push_back(rb.get());
    }

    // Check for collisions within the same cell and neighboring cells
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    int nx = x + i;
                    int ny = y + j;

                    if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                        for (auto& ballA : grid[x][y]) {
                            for (auto& ballB : grid[nx][ny]) {
                                if (ballA != ballB) {

                                    resolveBallCollision(*ballA, *ballB);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CollisionSystem::resolveHollowCircleCollision(std::shared_ptr<RigidbodyComponent>& ball, const sf::Vector2f& boundaryPosition, float boundaryRadius) {
    sf::Vector2f delta = ball->getOwner()->getPosition() - boundaryPosition;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float ballRadius = ball->getRadius();

    // Ensure the ball remains inside the boundary
    if (distance >= boundaryRadius - ballRadius) {
        sf::Vector2f normal = delta / distance; // Get direction from boundary center to ball

        // Reflect velocity based on collision normal
        sf::Vector2f velocity = ball->getVelocity();
        float dotProduct = (velocity.x * normal.x + velocity.y * normal.y);
        sf::Vector2f reflection = velocity - 2.0f * dotProduct * normal;

        ball->applyVelocity(reflection * 0.8f); // Apply velocity damping (80% energy retained)
        ball->applyVelocity(ball->getVelocity() * 0.99f); // Apply additional friction

        // Move ball just outside the boundary to prevent overlapping
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