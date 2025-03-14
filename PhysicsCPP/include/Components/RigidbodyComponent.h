#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>

class RigidbodyComponent : public Component {
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;

    RigidbodyComponent(float mass = 1.0f);

    void ApplyForce(const sf::Vector2f& force);
    void Update(float deltaTime) override;

    void Draw(sf::RenderWindow& window) const override {
        // Rigidbody does NOT need to be drawn, so leave empty
    }
};
