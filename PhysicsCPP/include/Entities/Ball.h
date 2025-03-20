#pragma once
#include <SFML/Graphics.hpp>
#include "Components/RigidbodyComponent.h"
#include "Components/RendererComponent.h"
#include "PhysicsConstants.h"

class Ball : public BaseEntity {
private:
    float radius;
    std::shared_ptr<RigidbodyComponent> rigidbody;
    std::shared_ptr<RendererComponent> renderer;

public:
    Ball(sf::Vector2f position);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    std::shared_ptr<RendererComponent> getRenderer() const;
    std::shared_ptr<RigidbodyComponent> getRigidbody();

    void accelerate(sf::Vector2f a);
    void resetForces();

    float getRadius() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& vel);
    float getGravity() const;
};
