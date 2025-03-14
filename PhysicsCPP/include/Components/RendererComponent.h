#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"

class RendererComponent : public Component {
private:
    sf::CircleShape shape;

public:
    RendererComponent(float radius, sf::Color color);

    void Update(float deltaTime) override {}
    void Draw(sf::RenderWindow& window) const override;

    void SetPosition(const sf::Vector2f& position);
};