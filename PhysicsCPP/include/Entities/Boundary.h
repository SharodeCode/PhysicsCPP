#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/BaseEntity.h"
#include "Components/RigidbodyComponent.h"

class Boundary : public BaseEntity {
private:
    sf::CircleShape frame;
    std::shared_ptr<RigidbodyComponent> rigidbody;
    float radius;

public:
    Boundary(float radius, sf::Vector2f position);

    float getRadius() const;

    std::shared_ptr<RigidbodyComponent> getRigidbody() const { return rigidbody; }

    // Implement required functions from BaseEntity
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
};
