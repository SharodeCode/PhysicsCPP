#include "Components/RendererComponent.h"


RendererComponent::RendererComponent(float radius, sf::Color color, BaseEntity* entity) : owner(entity) {
    shape.setRadius(radius);
    shape.setFillColor(color);
    shape.setOrigin(radius, radius);
}

RendererComponent::RendererComponent(const sf::Texture& texture, BaseEntity* entity) : owner(entity) {
    sprite.setTexture(texture);
    sprite.setOrigin(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2));
}

RendererComponent::RendererComponent(float radius, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, BaseEntity* entity) : owner(entity) {
    shape.setRadius(radius);
    shape.setFillColor(fillColor);  // Likely transparent
    shape.setOutlineThickness(outlineThickness);
    shape.setOutlineColor(outlineColor);
	shape.setOrigin(radius, radius);

	owner->setPosition(sf::Vector2(400.0f, 400.0f));
}



void RendererComponent::draw(sf::RenderWindow& window) const {
    if (owner) {
        sf::Vector2f pos = owner->getPosition();
        const_cast<sf::CircleShape&>(shape).setPosition(pos);
        const_cast<sf::Sprite&>(sprite).setPosition(pos);
    }

    if (sprite.getTexture()) {
        window.draw(sprite);
    }
    else {
        window.draw(shape);
    }
}
