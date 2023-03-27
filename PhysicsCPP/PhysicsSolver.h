

#pragma once
#include <vector>
#include "Ball.h"
#include <SFML/Graphics.hpp>

constexpr float damping = 0.99f;

class PhysicsSolver
{
public:

    PhysicsSolver();

    void spawnCircle(const sf::Vector2f& position);
    void update(float deltaTime);
    void applyGravity();
    void resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius);
    void resolveBallCollision(Ball& a, Ball& b);
    void checkFrameCollisions(float deltaTime);
    void checkBallCollisions();
    const std::vector<Ball>& getBalls() const;
    const sf::CircleShape& getFrame() const;

private:

	sf::CircleShape frame;
	std::vector<Ball> balls;
};

