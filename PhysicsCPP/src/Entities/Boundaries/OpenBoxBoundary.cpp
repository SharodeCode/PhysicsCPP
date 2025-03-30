#include "Entities/Boundaries/OpenBoxBoundary.h"
#include "Engine/CollisionSystem.h"

OpenBoxBoundary::OpenBoxBoundary(const sf::Vector2f& center, float width, float height, float thickness) : center(center) {
    // Left
    walls.push_back(std::make_shared<BoundaryWall>(
        sf::Vector2f(thickness, height),
        sf::Vector2f(-width / 2.f + thickness / 2.f, 0.f),
        center
    ));

    // Right
    walls.push_back(std::make_shared<BoundaryWall>(
        sf::Vector2f(thickness, height),
        sf::Vector2f(width / 2.f - thickness / 2.f, 0.f),
        center
    ));

    // Bottom
    walls.push_back(std::make_shared<BoundaryWall>(
        sf::Vector2f(width, thickness),
        sf::Vector2f(0.f, height / 2.f - thickness / 2.f),
        center
    ));
}

void OpenBoxBoundary::resolve(std::shared_ptr<RigidbodyComponent>& rb) const {
    if (!rb || !rb->getPool()) return;

    // Get a mutable reference to the ball data
    auto& data = rb->getPool()->ballData[rb->getIndex()];
    CollisionSystem::resolveBoxWallCollisions(*rb, walls);
}

void OpenBoxBoundary::draw(sf::RenderWindow& window) const {
    if (auto renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);
    }

    for (const auto& wall : walls) {
        wall->draw(window);
    }

}