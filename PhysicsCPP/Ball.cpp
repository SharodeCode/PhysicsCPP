#include<SFML/Graphics.hpp>
#include "Ball.h"

Ball::Ball(sf::Vector2f position) : circleRadius(8.0f), velocity(0.0f, 0.0f)
{
    shape = sf::CircleShape(circleRadius);
    shape.setFillColor(sf::Color::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
    shape.setOrigin(sf::Vector2f(circleRadius, circleRadius));
    setPosition(position);
    position_last = position;
}

void Ball::update(float dt) {

    const sf::Vector2f displacement = getPosition() - position_last;

    position_last = getPosition();

    setPosition(getPosition() + displacement + velocity * (dt * dt));

    velocity = {};
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

float Ball::getGravity() const
{
    return GRAVITY;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}
