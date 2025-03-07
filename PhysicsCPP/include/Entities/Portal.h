#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"

class Portal
{
public:
	Portal(PhysicsEngine* physicsSolver, sf::Sprite* sprite);

	void addPortal(sf::Vector2f position);

	void update(float deltaTime);

	void drawPortals(sf::RenderWindow* RenderWindow);

private:
	PhysicsEngine* ps;
	sf::Sprite* m_sprite;

	float spawnTime = 0;

	std::vector<sf::Vector2f> ballSpawners;
};

