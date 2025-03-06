#pragma once
#include <SFML/Graphics.hpp>
#include "PhysicsEngine/PhysicsSolver.h"
#include "Button.h"

class UI
{
public:
	UI(sf::RenderWindow *RenderWindow, PhysicsSolver* ps);
	void updateUI(float deltaTime);
	void displayFPS(float fps);
	void displayNumberOfObjects(int numberOfObjects);
	void InitialiseButtons();
	bool handleEvent(const sf::Event& event);

	std::shared_ptr<UIPanel> m_UIPanel;

private:
	sf::RenderWindow *m_RenderWindow;
	PhysicsSolver *physicsSolver;
	sf::Text textFPS;
	sf::Text textNumberOfObjects;
	sf::Font font;
	float displayFramerateTime = 0.0f;

	std::vector<std::shared_ptr<UIElement>> elements;


};

