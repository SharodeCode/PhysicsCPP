#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsSolver.h"

class UI
{
public:
	UI(sf::RenderWindow *RenderWindow, PhysicsSolver* ps);
	void updateSimulationDetails(float deltaTime);
	void displayFPS(float fps);
	void displayNumberOfObjects(int numberOfObjects);

private:
	sf::RenderWindow *m_RenderWindow;
	PhysicsSolver *physicsSolver;
	sf::Text textFPS;
	 sf::Text textNumberOfObjects;
	 sf::Font font;
	float displayFramerateTime = 0.0f;

};

