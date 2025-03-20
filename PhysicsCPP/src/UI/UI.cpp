#include "UI/UI.h"
#include <iostream>

UI::UI(sf::RenderWindow* RenderWindow, PhysicsEngine* ps)
{
	m_RenderWindow = RenderWindow;
    physicsSolver = ps;

    // Initialise font and text
    if (!font.loadFromFile("./Media/Fonts/Roboto.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    textFPS.setFont(font);
    textFPS.setCharacterSize(10);
    textFPS.setFillColor(sf::Color::White);
    textFPS.setStyle(sf::Text::Regular);

    textNumberOfObjects.setFont(font);
    textNumberOfObjects.setCharacterSize(10);
    textNumberOfObjects.setFillColor(sf::Color::White);
    textNumberOfObjects.setStyle(sf::Text::Regular);
    textNumberOfObjects.setPosition(sf::Vector2f(0, textFPS.getLocalBounds().height + 12));
}

void UI::update(float deltaTime) {
    
    for (auto& button : elements) {
        button->update(sf::Mouse::getPosition(*m_RenderWindow));
    }
    
    // Update framerate
    displayFramerateTime += deltaTime;
    float fps = 1.0f / (deltaTime);

    if (displayFramerateTime > 0.5)
    {
        displayFPS(fps);
        displayFramerateTime = 0;
    }

    displayNumberOfObjects(static_cast<int>(physicsSolver->getRigidbodyCount()));
}

void UI::render(sf::RenderWindow& window) {
    if (m_UIPanel) {
        m_UIPanel->draw(window);  // Draw panel first
    }

    // Draw text elements after the panel
    window.draw(textFPS);
    window.draw(textNumberOfObjects);
}


void UI::displayFPS(float fps)
{
    textFPS.setString("FPS: " + std::to_string(fps));
}

void UI::displayNumberOfObjects(int numberOfObjects)
{
    textNumberOfObjects.setString("Number of objects: " + std::to_string(numberOfObjects));
}

bool UI::handleEvent(const sf::Event& event) {
    for (auto& element : elements) {
        if (element->handleEvent(event, sf::Mouse::getPosition(* m_RenderWindow))) {
            // Stop handling if an element handled the event
            return true;
        }
    }

    return false;
}
