#include "UI/UI.h"
#include <SFML/Graphics.hpp>
#include "UI/Button.h"
#include "Engine/PhysicsEngine.h"
#include <UI/UIPanel.h>

UI::UI(sf::RenderWindow* RenderWindow, PhysicsEngine* ps)
{
	m_RenderWindow = RenderWindow;
    physicsSolver = ps;

    // Initialise font and text
    font.loadFromFile("./Media/Fonts/Roboto.ttf");
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

void UI::updateUI(float deltaTime) {
    
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

    displayNumberOfObjects(static_cast<int>(physicsSolver->getBalls().size()));

    m_RenderWindow->draw(textFPS);
    m_RenderWindow->draw(textNumberOfObjects);

    for (auto& button : elements) {

        button->draw(*m_RenderWindow);
    }
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
