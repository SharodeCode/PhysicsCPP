#include "Entities/Portal.h"

Portal::Portal(const sf::Vector2f& pos, const sf::Texture& texture)
    : position(pos), spawner(10.0f) {
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(static_cast<float>(texture.getSize().x / 2), static_cast<float>(texture.getSize().y / 2)));
    sprite.setPosition(position);

    addComponent<RendererComponent>(texture);
}

void Portal::update(float deltaTime, std::vector<std::unique_ptr<Ball>>& balls) {
    timeSinceLastSpawn += deltaTime;

    if (timeSinceLastSpawn >= spawnCooldown) {
        balls.emplace_back(spawner.spawnBall(position));
        timeSinceLastSpawn = 0.0f;
    }
}

void Portal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Portal::update(float deltaTime) {
    // Implement the update logic here
}

void Portal::draw(sf::RenderWindow& window) const {
    window.draw(sprite); // or whatever needs to be drawn
}

