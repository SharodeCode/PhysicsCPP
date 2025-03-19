#include "Entities/Portal.h"

Portal::Portal(const sf::Vector2f& position, const sf::Texture& texture, std::vector<std::unique_ptr<Ball>>& ballList)
    : balls(ballList), spawner(10.0f) {
    setPosition(position);  // Now stored in BaseEntity

    // Attach Renderer Component
    auto renderer = addComponent<RendererComponent>(texture, nullptr);
}


void Portal::update(float deltaTime) {
    timeSinceLastSpawn += deltaTime;
    if (timeSinceLastSpawn >= spawnCooldown) {
        balls.emplace_back(spawner.spawnBall(position));
        timeSinceLastSpawn = 0.0f;
    }
}

void Portal::draw(sf::RenderWindow& window) const {
    if (std::shared_ptr<RendererComponent> renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);
    }
}

