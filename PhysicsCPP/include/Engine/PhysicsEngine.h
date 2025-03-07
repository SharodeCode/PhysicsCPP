#pragma once
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Boundary.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

constexpr float damping = 0.99f;

class PhysicsEngine
{
public:
    int subSteps;

    PhysicsEngine();

    void spawnCircle(const sf::Vector2f& position);
    void applyGravity();
    void checkBallCollisionsBruteForce();
    const std::vector<Ball>& getBalls() const;
    const sf::CircleShape& getFrame() const;
    void updateBalls(float dt);
    void update(float subStepRate);
    void toggleAudioActive();

private:
    Boundary boundary;
    std::vector<Ball> balls;
    bool audioActive = false;
};

