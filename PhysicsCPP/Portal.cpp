#include "Portal.h"
#include "PhysicsSolver.h"

Portal::Portal(PhysicsSolver* physicsSolver, sf::Sprite* sprite) {

    ps = physicsSolver;
    m_sprite = sprite;
}

void Portal::addPortal(sf::Vector2f position) {

    ballSpawners.emplace_back(position);
}

void Portal::drawPortals(sf::RenderWindow* RenderWindow) {
    for (auto& ballSpawner : ballSpawners) {

        m_sprite->setPosition(ballSpawner.x - 50, ballSpawner.y - 50);
        RenderWindow->draw(*m_sprite);
    }
}

void Portal::update(float deltaTime) {
	spawnTime += deltaTime;

    bool spawn = false;

    for (auto& ballSpawner : ballSpawners) {

        if (spawnTime > 0.2)
        {
            ps->spawnCircle(ballSpawner);
            spawn = true;
        }
    }

    if (spawn == true) {
        spawnTime = 0;
    }
}
