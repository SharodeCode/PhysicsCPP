#pragma once
#include <SFML/Graphics.hpp>
#include "Components/RigidbodyComponent.h"
#include <Components/RendererComponent.h>
#include "Components/Component.h"

class Ball : Component, public sf::Transformable {
private:
    float radius;
    sf::Vector2f position_last;
    RigidbodyComponent rigidbody;

    RendererComponent renderer;

public:
    Ball(sf::Vector2f position);

    void update(float dt);
    void Draw(sf::RenderWindow& window) const override;

    RendererComponent* GetRenderer();
    const RendererComponent* GetRenderer() const { return &renderer; }

    void accelerate(sf::Vector2f a);

    float getRadius() const;

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& vel);
    float getGravity() const;

    sf::Vector2f getPositionLast() const;
    void setPositionLast(const sf::Vector2f& pos);

    RigidbodyComponent* GetRigidbody() { return &rigidbody; }
};
