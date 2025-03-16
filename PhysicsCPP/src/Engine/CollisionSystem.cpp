#include "Engine/CollisionSystem.h"
#include <cmath>

void CollisionSystem::resolveBallCollision(Ball& a, Ball& b) {
    sf::Vector2f delta = a.getPosition() - b.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float collision_distance = a.getRadius() + b.getRadius();


    if (distance <= collision_distance) {
        sf::Vector2f normal = delta / distance;
        sf::Vector2f relative_velocity = (a.getPosition() - a.getPositionLast()) - (b.getPosition() - b.getPositionLast());
        float impulse = 2.0f * (relative_velocity.x * normal.x + relative_velocity.y * normal.y);


        if (impulse < -3.5f || impulse > 3.5f) {

            // Calculate the collision point
            sf::Vector2f collisionPoint = a.getPosition() + normal * (a.getRadius() - collision_distance);

        }


        const float delta = 0.65f * (distance - collision_distance);

        a.move(-((normal * delta * b.getRadius()) / (a.getRadius() + b.getRadius())));
        b.move((normal * delta * a.getRadius()) / (a.getRadius() + b.getRadius()));

    }
}

void CollisionSystem::checkBallCollisions(std::vector<std::unique_ptr<Ball>>& balls) {

    float CELL_SIZE = 40.0f;

    // Create the grid
    int gridWidth = static_cast<int>(std::ceil(800.0f / CELL_SIZE));
    int gridHeight = static_cast<int>(std::ceil(800.0f / CELL_SIZE));

    std::vector<std::vector<std::vector<Ball*>>> grid(gridWidth, std::vector<std::vector<Ball*>>(gridHeight));

    // Assign balls to grid cells
    for (auto& ball : balls) {
        int x = static_cast<int>(ball->getPosition().x / CELL_SIZE);
        int y = static_cast<int>(ball->getPosition().y / CELL_SIZE);

        grid[x][y].push_back(ball.get());
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

void CollisionSystem::resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& boundaryPosition, float boundaryRadius) {
    sf::Vector2f delta = ball.getPosition() - boundaryPosition;

    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float ballRadius = ball.getRadius();

    if (distance >= boundaryRadius - ballRadius) {
        sf::Vector2f normal = delta / distance;

        ball.setVelocity(ball.getVelocity() - (0.8f * (ball.getVelocity().x * normal.x + ball.getVelocity().y * normal.y) * normal));
        ball.setVelocity(ball.getVelocity() * 0.99f);

        ball.setPosition(boundaryPosition + normal * (boundaryRadius - ballRadius));
    }
}

void CollisionSystem::checkBallCollisionsBruteForce(std::vector<Ball>& balls) {
    for (size_t i = 0; i < balls.size(); ++i) {
        for (size_t j = i + 1; j < balls.size(); ++j) {
            resolveBallCollision(balls[i], balls[j]);
        }
    }
}