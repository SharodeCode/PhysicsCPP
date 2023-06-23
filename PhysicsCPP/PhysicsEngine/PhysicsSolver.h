#pragma once
#include <vector>
#include "Objects/Ball.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Effects/ParticleSystem.h"

constexpr float damping = 0.99f;

class PhysicsSolver
{
public:
    int subSteps;

    PhysicsSolver(ParticleSystem* sparkss);

    void spawnCircle(const sf::Vector2f& position);
    void applyGravity();
    void resolveHollowCircleCollision(Ball& ball, const sf::Vector2f& center, float outerRadius);
    void resolveBallCollision(Ball& a, Ball& b);
    void checkFrameCollisions();
    void checkBallCollisionsBruteForce();
    void checkBallCollisionsCollisionGrid();
    void processGridRange(std::vector<Ball>& balls, const std::vector<std::vector<std::vector<Ball*>>>& grid, int startX, int startY, int endX, int endY);
    const std::vector<Ball>& getBalls() const;
    const sf::CircleShape& getFrame() const;
    void updateBalls(float dt);
    void update(float subStepRate);
    void toggleAudioActive();

private:

	sf::CircleShape frame;
	std::vector<Ball> balls;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool audioActive = false;
    ParticleSystem* sparks;
};

