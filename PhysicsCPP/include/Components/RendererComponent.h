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

    void Update(float deltaTime) override {}
    void Draw(sf::RenderWindow& window) const override;

    void SetPosition(const sf::Vector2f& position);
};