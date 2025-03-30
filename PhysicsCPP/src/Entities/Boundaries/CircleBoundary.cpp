#include "Entities/Boundaries/CircleBoundary.h"

CircleBoundary::CircleBoundary(const sf::Vector2f& center, float radius)
    : center(center), radius(radius) {
    addComponent<RendererComponent>(radius, sf::Color::Transparent, sf::Color::White, 3.f, this);

}

void CircleBoundary::resolve(std::shared_ptr<RigidbodyComponent>& rb) const {
    auto* pool = rb->getPool();
    int idx = rb->getIndex();
    CollisionSystem::resolveHollowCircleCollision(*pool, idx, radius, center);
}

void CircleBoundary::draw(sf::RenderWindow& window) const {
    if (auto renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);
    }
}
