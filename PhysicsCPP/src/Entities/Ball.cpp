#include "Entities/Ball.h"
#include "PhysicsConstants.h"

Ball::Ball(sf::Vector2f position) : radius(10.0f), rigidbody(1.0f) {
    shape = sf::CircleShape(radius);
    shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
    shape.setOrigin(sf::Vector2f(radius, radius));
    setPosition(position);
    position_last = position;
}

void Ball::update(float dt) {
    sf::Vector2f displacement = getPosition() - position_last;
    position_last = getPosition();

    rigidbody.Update(dt);
    setPosition(getPosition() + displacement + rigidbody.velocity * (dt * dt));
}

void Ball::accelerate(sf::Vector2f a) {
    rigidbody.ApplyForce(a * rigidbody.mass);
}

sf::Vector2f Ball::getVelocity() const {
    return rigidbody.velocity;
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    rigidbody.velocity = vel;
}

float Ball::getGravity() const {
    return GRAVITY;
}

sf::Vector2f Ball::getPositionLast() const {
    return position_last;
}

void Ball::setPositionLast(const sf::Vector2f& pos) {
    position_last = pos;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(shape, states);
}
