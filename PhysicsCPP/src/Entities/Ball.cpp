#include "Entities/Ball.h"


Ball::Ball(sf::Vector2f position) : radius(10.0f) {
    setPosition(position);

    positionLast = position;

    // Generate a random color
    sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);

    rigidbody = addComponent<RigidbodyComponent>(this, RigidbodyComponent::Type::Dynamic, 10.0f);

    addComponent<RendererComponent>(radius, randomColor, this);
}

void Ball::update(float deltaTime) {

    sf::Vector2f prevPosition = getPosition();
    sf::Vector2f displacement = getPosition() - positionLast;
    positionLast = prevPosition; // Store before moving

    rigidbody->update(deltaTime);
    setPosition(getPosition() + displacement + rigidbody->velocity * (deltaTime * deltaTime));

    if (std::shared_ptr renderer = getComponent<RendererComponent>().lock()) {
        setPosition(getPosition());
    }
}

void Ball::accelerate(sf::Vector2f a) {
    rigidbody->applyForce(a);
}

void Ball::resetForces() {
	rigidbody->resetForces();
}

sf::Vector2f Ball::getVelocity() const {
    return rigidbody->velocity;
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    rigidbody->velocity = vel;
}

float Ball::getGravity() const {
    return GRAVITY;
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
    return rigidbody;
}

std::shared_ptr<RendererComponent> Ball::getRenderer() const {
    return renderer;
}