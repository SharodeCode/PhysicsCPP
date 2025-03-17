#include "Entities/Ball.h"
#include "PhysicsConstants.h"

Ball::Ball(sf::Vector2f position) : radius(10.0f), rigidbody(0.5f) {
    setPosition(position);
    positionLast = position;

    // Generate a random color
    sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);

    addComponent<RigidbodyComponent>();
    addComponent<RendererComponent>(radius, randomColor);
    getRenderer()->setPosition(position);
}

void Ball::update(float deltaTime) {

    sf::Vector2f prevPosition = getPosition();
    sf::Vector2f displacement = getPosition() - positionLast;
    positionLast = prevPosition; // Store before moving

    rigidbody.update(deltaTime);
    setPosition(getPosition() + displacement + rigidbody.velocity * (deltaTime * deltaTime));

    if (std::shared_ptr renderer = getComponent<RendererComponent>().lock()) {
        renderer->setPosition(getPosition());
    }
}

void Ball::accelerate(sf::Vector2f a) {
    rigidbody.applyForce(a);
}

void Ball::resetForces() {
	rigidbody.resetForces();
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
    return positionLast;
}

void Ball::setPositionLast(const sf::Vector2f& pos) {
    positionLast = pos;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::draw(sf::RenderWindow& window) const {
    if (const std::shared_ptr<RendererComponent> renderer = getRenderer()) {
        renderer->draw(window);
    }
}

std::shared_ptr<RigidbodyComponent> Ball::getRigidbody() {
    return getComponent<RigidbodyComponent>().lock();
}

std::shared_ptr<RendererComponent> Ball::getRenderer() const {
    return getComponent<RendererComponent>().lock();
}