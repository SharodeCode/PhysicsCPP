#pragma once
#include <SFML/System/Vector2.hpp>
#include "Component.h"
#include "Entities/BaseEntity.h"

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

    RigidbodyComponent(BaseEntity* owner, Type type, float radius) : owner(owner), type(type), mass(0.05f), radius(radius) {}

    void applyForce(const sf::Vector2f& force);
    void resetForces();
    void update(float deltaTime) override;

    void move(const sf::Vector2f& displacement);
    float getRadius() const { return radius; }

    BaseEntity* getOwner() const { return owner; }

	void applyVelocity(const sf::Vector2f& vel) { velocity = vel; }
	sf::Vector2f getVelocity() const { return velocity; }

	float getMass() const { return mass; }

	Type getType() const { return type; }

private:
    BaseEntity* owner;
    Type type;

};
