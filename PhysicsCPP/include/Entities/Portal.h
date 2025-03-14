#pragma once
#include "Entities/Ball.h"
#include "Entities/Spawner.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Portal: public sf::Drawable {
private:
    sf::Vector2f position;
    sf::Sprite sprite;
    Spawner spawner;
    float spawnCooldown = 0.05f;
    float timeSinceLastSpawn = 0.0f;

public:
    Portal(const sf::Vector2f& position, const sf::Texture& texture);

    void update(float deltaTime, std::vector<Ball>& balls);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
