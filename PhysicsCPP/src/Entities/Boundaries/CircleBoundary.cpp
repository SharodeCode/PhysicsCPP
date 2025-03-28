#include "Entities/Boundaries/CircleBoundary.h"

CircleBoundary::CircleBoundary(const sf::Vector2f& center, float radius)
    : center(center), radius(radius) {
    setPosition(center);
    addComponent<RendererComponent>(radius, sf::Color::Transparent, sf::Color::White, 3.f, this);

}

void CircleBoundary::resolve(std::shared_ptr<RigidbodyComponent>& rb) const {
    CollisionSystem::resolveHollowCircleCollision(rb, center, radius);
}

void CircleBoundary::draw(sf::RenderWindow& window) const {
    if (auto renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);
    }
}
