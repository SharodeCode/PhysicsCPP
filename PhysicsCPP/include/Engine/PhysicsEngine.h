#pragma once
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Boundary.h"
#include "Entities/Spawner.h"
#include "Entities/Portal.h"
#include <SFML/Graphics.hpp>

class PhysicsEngine {
private:
    std::vector<std::unique_ptr<Ball>> balls;
    std::vector<Portal> portals;
    Boundary boundary;
    Spawner spawner;
    bool audioActive = false;

public:
    int subStepCount = 1;

    PhysicsEngine();
    void update(float subStepRate);
    void spawnBall(const sf::Vector2f& position);
    void addPortal(const sf::Vector2f& position, const sf::Texture& texture);
    void applyGravity();
    void updateBalls(float dt);

    const std::vector<std::unique_ptr<Ball>>& getBalls() const;
    const std::vector<Portal>& getPortals() const;
    const sf::CircleShape& getBoundaryShape() const;
    void toggleAudioActive();
};
