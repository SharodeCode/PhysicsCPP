#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable, public sf::Transformable
{

public:
    sf::Vector2f position_last;
    float        radius = 2.0f;

    Ball(sf::Vector2f position);

    void update(float dt);

    void bounce(sf::Vector2f normal, float damping = 0.88f);

    void accelerate(sf::Vector2f a);

    float getRadius() const;
    float getGravity() const;

    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(const sf::Vector2f& vel) { velocity = vel; }

private:
    sf::Vector2f velocity;
    sf::CircleShape shape;

    const float GRAVITY = 9.8f * 150;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


