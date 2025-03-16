#include "Components/RigidbodyComponent.h"

RigidbodyComponent::RigidbodyComponent(float mass)
    : mass(mass), velocity(0.f, 0.f), acceleration(0.f, 0.f) {}

void RigidbodyComponent::ApplyForce(const sf::Vector2f& force) {
    acceleration += force / mass;
}

void RigidbodyComponent::update(float deltaTime) {
    velocity += acceleration * deltaTime;
    acceleration = { 0.f, 0.f };
}
