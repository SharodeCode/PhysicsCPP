#pragma once
#include <SFML/Graphics.hpp>

class Boundary {
private:
    sf::CircleShape frame;

public:
    Boundary(float radius, sf::Vector2f position);

    const sf::CircleShape& getFrame() const;
    float getRadius() const;
    sf::Vector2f getPosition() const;
};
