#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>

class BaseEntity;

class RigidbodyComponent : public Component {
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float radius;

    enum class Type {
        Static,  // Unmovable (e.g., walls, ground, boundaries)
        Dynamic  // Movable (e.g., balls, objects)
    };

    RigidbodyComponent(BaseEntity* owner, Type type, float radius) : owner(owner), type(type), mass(5.0f), radius(radius) {}
    RigidbodyComponent(float mass = 100.0f);

    void applyForce(const sf::Vector2f& force);
    void resetForces();
    void update(float deltaTime) override;

    void move(const sf::Vector2f& displacement);
    float getRadius() const { return radius; }

    BaseEntity* getOwner() const { return owner; }

	sf::Vector2f setVelocity(const sf::Vector2f& vel) { return velocity = vel; }
	sf::Vector2f getVelocity() const { return velocity; }

	float getMass() const { return mass; }

private:
    BaseEntity* owner;
    Type type;

};
