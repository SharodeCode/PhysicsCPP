#include "Components/RendererComponent.h"

RendererComponent::RendererComponent(float radius, sf::Color color) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
}

RendererComponent::RendererComponent(const sf::Texture& texture) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2));
}

void RendererComponent::draw(sf::RenderWindow& window) const {
    if (sprite.getTexture()) {
        window.draw(sprite); // Draw the texture for portals
    }
    else {
        window.draw(shape); // Draw the circle shape for balls
    }
}

void RendererComponent::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}
