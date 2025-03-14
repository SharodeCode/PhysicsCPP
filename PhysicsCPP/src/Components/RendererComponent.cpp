#include "Components/RendererComponent.h"

RendererComponent::RendererComponent(float radius, sf::Color color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
}

void RendererComponent::Draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

void RendererComponent::SetPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}
