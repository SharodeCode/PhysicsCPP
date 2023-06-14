#include "UI.h"
#include <SFML/Graphics.hpp>
#include "Button.h"

UI::UI(sf::RenderWindow* RenderWindow, PhysicsSolver* ps)
{
	m_RenderWindow = RenderWindow;
    physicsSolver = ps;

    UI::InitialiseButtons();

    // Initialise font and text
    font.loadFromFile("Roboto.ttf");
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

void UI::InitialiseButtons() {

    const float buttonWidth = 200.f;
    const float buttonHeight = 50.f;
    const float buttonGap = 10.f;

    buttons.emplace_back(Button((m_RenderWindow->getSize().x - 200.f), 0.f, buttonWidth, buttonHeight, "Mute", font));
    buttons.emplace_back(Button((m_RenderWindow->getSize().x - 200.f), (buttonHeight + buttonGap), buttonWidth, buttonHeight, "Ball Spawner", font));
    buttons.emplace_back(Button((m_RenderWindow->getSize().x - 200.f), ((2 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Cilck to Spawn", font));
}

void UI::updateUI(float deltaTime) {

    // Update buttons
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        for (auto& button : buttons) {

            if (button.isMouseOver(*m_RenderWindow)) {
                int a = 0;
            }
        }


    }
    
    for (auto& button : buttons) {

        button.update(*m_RenderWindow);
    }
    

    // Update framerate
    displayFramerateTime += deltaTime;
    float fps = 1.0f / (deltaTime);

    if (displayFramerateTime > 0.5)
    {
        displayFPS(fps);
        displayFramerateTime = 0;
    }

    displayNumberOfObjects(physicsSolver->getBalls().size());

    m_RenderWindow->draw(textFPS);
    m_RenderWindow->draw(textNumberOfObjects);

    for (auto& button : buttons) {

        button.drawTo(*m_RenderWindow);
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

