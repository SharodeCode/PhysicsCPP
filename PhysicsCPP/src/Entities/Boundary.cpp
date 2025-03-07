#include "Entities/Boundary.h"

Boundary::Boundary(float radius, sf::Vector2f position) {
    frame = sf::CircleShape(radius, 100);
    frame.setOutlineThickness(10.0f);
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::White);
    frame.setOrigin(sf::Vector2(radius, radius));
    frame.setPosition(position);
}

const sf::CircleShape& Boundary::getFrame() const {
    return frame;
}

float Boundary::getRadius() const {
    return frame.getRadius();
}

sf::Vector2f Boundary::getPosition() const {
    return frame.getPosition();
}
