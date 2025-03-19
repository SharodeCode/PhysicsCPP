#include "Engine/InputManager.h"

InputManager::InputManager(PhysicsEngine& engine, UI& uiInstance, sf::RenderWindow& win, SceneManager* sceneManager)
    : physicsEngine(engine), ui(uiInstance), window(win), sceneManager(sceneManager) {
    if (!texture.loadFromFile("./Media/Images/portal.png")) {
        // Handle texture load failure
    }
}

void InputManager::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            bool UIClicked = ui.handleEvent(event);

            if (Button* activeButton = dynamic_cast<Button*>(ui.m_UIPanel->getActiveElement())) {
                currentButton = activeButton->m_btnType;
            }

            if (!UIClicked) {
                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                if (currentButton == Button::buttonType::clickToSpawn) {
					sceneManager->handleInput(InputAction::SpawnBall, mousePosition);
                }
                else if (currentButton == Button::buttonType::ballSpawner) {
                    sceneManager->handleInput(InputAction::SpawnPortal, mousePosition);
                }
            }
        }
    }
}
