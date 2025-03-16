#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"

class RendererComponent : public Component {
private:
    sf::CircleShape shape;
    sf::Sprite sprite;

public:
    RendererComponent(float radius, sf::Color color);
    RendererComponent(const sf::Texture& texture);

    void update(float deltaTime) override {}
    void draw(sf::RenderWindow& window) const override;

    void setPosition(const sf::Vector2f& position);
};