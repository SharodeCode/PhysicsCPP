#include "Entities/Portal.h"

Portal::Portal(const sf::Vector2f& position, const sf::Texture& texture, std::vector<std::unique_ptr<Ball>>& ballList)
    : position(position), balls(ballList), spawner(10.0f) {
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2)));
    sprite.setPosition(position);

    addComponent<RendererComponent>(texture);
}

void Portal::update(float deltaTime) {
    timeSinceLastSpawn += deltaTime;
    if (timeSinceLastSpawn >= spawnCooldown) {
        balls.emplace_back(spawner.spawnBall(position));
        timeSinceLastSpawn = 0.0f;
    }
}

void Portal::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

