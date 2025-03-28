#pragma once
#include <SFML/System.hpp>
#include "BaseBoundary.h"
#include "Components/RigidbodyComponent.h"
#include "Engine/CollisionSystem.h"


class CircleBoundary : public BaseEntity, public BaseBoundary {
public:
    CircleBoundary(const sf::Vector2f& center, float radius);

    void resolve(std::shared_ptr<RigidbodyComponent>& rb) const override;
    void update(float) override {}
    void draw(sf::RenderWindow&) const override;

private:
    sf::Vector2f center;
    float radius;
};
