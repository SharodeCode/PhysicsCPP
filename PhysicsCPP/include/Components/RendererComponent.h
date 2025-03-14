#pragma once
#include <SFML/Graphics.hpp>

class RendererComponent {
private:
    sf::CircleShape shape;

public:
    RendererComponent(float radius, sf::Color color);

    void Draw(sf::RenderWindow& window) const;
    void SetPosition(const sf::Vector2f& position);
};