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

RendererComponent::RendererComponent(const sf::Vector2f& size, sf::Color fillColor, BaseEntity* entity)
    : owner(entity)
{
    rect.setSize(size);
    rect.setFillColor(fillColor);
    rect.setOrigin(size.x / 2.f, size.y / 2.f);
}



void RendererComponent::draw(sf::RenderWindow& window) const {
    if (!owner) return;

    sf::Vector2f pos = owner->getPosition();

    if (sprite.getTexture()) {
        const_cast<sf::Sprite&>(sprite).setPosition(pos);
        window.draw(sprite);
    }
    else if (shape.getRadius() > 0) {
        const_cast<sf::CircleShape&>(shape).setPosition(pos);
        window.draw(shape);
    }
    else {
        const_cast<sf::RectangleShape&>(rect).setPosition(pos);
        window.draw(rect);
    }
}


void RendererComponent::move(const sf::Vector2f& offset) {

    if (shape.getRadius() > 0) {
        shape.move(offset);
    }
    else {
        rect.move(offset);
    }
}

sf::Vector2f RendererComponent::getSize() const {
    if (shape.getRadius() > 0) {
        float diameter = shape.getRadius() * 2.f;
        return sf::Vector2f(diameter, diameter);
    }
    else {
        return rect.getSize();
    }
}