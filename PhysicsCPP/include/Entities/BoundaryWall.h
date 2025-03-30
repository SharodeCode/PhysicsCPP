#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/BaseEntity.h"
#include "Components/RendererComponent.h"

class BoundaryWall : public BaseEntity {
private:
    sf::Vector2f position;

public:
    BoundaryWall(const sf::Vector2f& size, const sf::Vector2f& offset, const sf::Vector2f& center) : position(center + offset) {
        addComponent<RendererComponent>(size, sf::Color::White, this);
    }

    sf::Vector2f getPosition() const { return position; }

    void update(float deltaTime) override {}
    void draw(sf::RenderWindow& window) const override {
        if (auto renderer = getComponent<RendererComponent>().lock()) {
            renderer->draw(window);
        }
    }
};