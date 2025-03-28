#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/BaseEntity.h"
#include "Components/RendererComponent.h"

class BoundaryWall : public BaseEntity {
public:
    BoundaryWall(const sf::Vector2f& size, const sf::Vector2f& offset, const sf::Vector2f& center) {
        addComponent<RendererComponent>(size, sf::Color::White, this);
        setPosition(center + offset);
        setPositionLast(center + offset);
    }

    void update(float deltaTime) override {}
    void draw(sf::RenderWindow& window) const override {
        if (auto renderer = getComponent<RendererComponent>().lock()) {
            renderer->draw(window);
        }
    }
};