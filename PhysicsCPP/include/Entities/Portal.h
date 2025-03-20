#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Spawner.h"

class Portal: public BaseEntity {
private:
    sf::Vector2f position;
    sf::Sprite sprite;
    Spawner spawner;
    float spawnCooldown = 0.05f;
    float timeSinceLastSpawn = 0.0f;

    std::vector<std::unique_ptr<Ball>>& balls;

public:
    Portal(const sf::Vector2f& position, const sf::Texture& texture, std::vector<std::unique_ptr<Ball>>& ballList);

    // Disable copying to prevent reference issues
    Portal(const Portal&) = delete;
    Portal& operator=(const Portal&) = delete;

    // Allow moving
    Portal(Portal&&) = default;
    Portal& operator=(Portal&&) = default;

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
};