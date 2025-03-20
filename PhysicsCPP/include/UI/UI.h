#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "UI/Button.h"
#include "UI/UIPanel.h"

class UI
{
public:
	UI(sf::RenderWindow *RenderWindow, PhysicsEngine* ps);
	void update(float deltaTime);
	void displayFPS(float fps);
	void displayNumberOfObjects(int numberOfObjects);
	bool handleEvent(const sf::Event& event);
	sf::Font& getFont() { return font; }
	void render(sf::RenderWindow& window);

	std::shared_ptr<UIPanel> m_UIPanel;
	std::vector<std::shared_ptr<UIElement>> elements;

private:
	sf::RenderWindow *m_RenderWindow;
	PhysicsEngine *physicsSolver;
	sf::Text textFPS;
	sf::Text textNumberOfObjects;
	sf::Font font;
	float displayFramerateTime = 0.0f;




};

