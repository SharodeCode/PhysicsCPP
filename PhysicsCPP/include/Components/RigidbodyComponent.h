#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>

class RigidbodyComponent : public Component {
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    RigidbodyComponent(float mass = 100.0f);

    void applyForce(const sf::Vector2f& force);
    void resetForces();
    void update(float deltaTime) override;
};
