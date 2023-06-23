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
	bool isButtonClicked();
	Button::buttonType buttonClicked();

private:
	sf::RenderWindow *m_RenderWindow;
	PhysicsSolver *physicsSolver;
	sf::Text textFPS;
	sf::Text textNumberOfObjects;
	sf::Font font;
	float displayFramerateTime = 0.0f;

	std::vector<Button> buttons;

};

