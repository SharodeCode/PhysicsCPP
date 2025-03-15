#pragma once
#include <SFML/Graphics.hpp>
#include "Components/RigidbodyComponent.h"
#include <Components/RendererComponent.h>
#include "Components/Component.h"
#include "Entities/BaseEntity.h"

class Ball : public BaseEntity, public sf::Transformable {
private:
    float radius;
    sf::Vector2f position_last;
    RigidbodyComponent rigidbody;

public:
    Ball(sf::Vector2f position);

    void Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window) const override;

    RendererComponent* GetRenderer() const;
    RigidbodyComponent* GetRigidbody();

    void accelerate(sf::Vector2f a);

    float getRadius() const;

    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& vel);
    float getGravity() const;

    sf::Vector2f getPositionLast() const;
    void setPositionLast(const sf::Vector2f& pos);
};
