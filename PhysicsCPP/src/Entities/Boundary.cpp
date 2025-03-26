#include "Entities/Boundary.h"

Boundary::Boundary(float radius, sf::Vector2f position) : radius(radius) {
    rigidbody = std::make_shared<RigidbodyComponent>(this, RigidbodyComponent::Type::Static, radius);
    addComponent<RendererComponent>(radius, sf::Color::Transparent, sf::Color::White, 10.0f, this);

    setPosition(position);               // Sets center position
    setPositionLast(position);          // Required for Verlet-style bodies
}

float Boundary::getRadius() const {
    return radius;
}

void Boundary::update(float deltaTime) {
    // Static boundary does not need to update
}

void Boundary::draw(sf::RenderWindow& window) const {
    if (auto renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);  // Let the renderer handle the drawing
    }
}
