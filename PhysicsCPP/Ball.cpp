#include<SFML/Graphics.hpp>
#include "Ball.h"

Ball::Ball(sf::Vector2f position) : circleRadius(5.0f), velocity(0, 0)
{
    shape = sf::CircleShape(circleRadius);
    shape.setFillColor(sf::Color::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
    shape.setOrigin(sf::Vector2f(circleRadius, circleRadius));
    setPosition(position);
}

void Ball::update(float dt) {
    sf::Vector2f pos = getPosition();
    pos += velocity * dt;

    setPosition(pos);
}

void Ball::bounce(sf::Vector2f normal, float damping) {
    float dot = velocity.x * normal.x + velocity.y * normal.y;
    if (dot < 0) {
        velocity.x -= 2 * dot * normal.x * damping;
        velocity.y -= 2 * dot * normal.y * damping;
    }
}

void Ball::accelerate(sf::Vector2f a)
{
    velocity += a;
}

float Ball::getRadius() const
{
    return circleRadius;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}