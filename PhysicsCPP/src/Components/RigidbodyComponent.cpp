#include "Components/RigidbodyComponent.h"

void RigidbodyComponent::applyForce(const sf::Vector2f& force) {
    acceleration += force / mass;
}

void RigidbodyComponent::update(float deltaTime) {
    //velocity += acceleration * deltaTime;
    //acceleration = { 0.f, 0.f };

    //if (owner) {
    //    owner->setPosition(owner->getPosition() + velocity * deltaTime);
    //}
}

void RigidbodyComponent::resetForces() {
    acceleration = { 0.f, 0.f };
}

void RigidbodyComponent::move(const sf::Vector2f& displacement) {
    auto& data = pool->ballData[physicsIndex];
    data.x += displacement.x;
    data.y += displacement.y;
}
