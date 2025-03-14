#include "Entities/Portal.h"

Portal::Portal(const sf::Vector2f& pos, const sf::Texture& texture)
    : position(pos), spawner(10.0f) {
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2));
    sprite.setPosition(position);
}

void Portal::update(float deltaTime, std::vector<Ball>& balls) {
    timeSinceLastSpawn += deltaTime;

    if (timeSinceLastSpawn >= spawnCooldown) {
        balls.emplace_back(spawner.spawnBall(position));
        timeSinceLastSpawn = 0.0f;
    }
}

void Portal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}
