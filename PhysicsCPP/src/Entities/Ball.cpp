#include "Entities/Ball.h"


Ball::Ball(sf::Vector2f position, PhysicsDataPool* pool, int index)
    : radius(GameConfig::BALL_RADIUS),
    physicsData(pool), physicsIndex(index)
{
    sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);
    color = randomColor;

    rigidbody = addComponent<RigidbodyComponent>(this, RigidbodyComponent::Type::Dynamic, radius);
    rigidbody->setPhysicsData(pool, index);

    addComponent<RendererComponent>(radius, randomColor, this);

    setPosition(position);
}


void Ball::update(float deltaTime) {

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