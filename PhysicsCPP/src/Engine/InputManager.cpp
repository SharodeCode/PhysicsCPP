#include "Engine/InputManager.h"

InputManager::InputManager(PhysicsEngine& engine, UI& uiInstance, sf::RenderWindow& win, SceneManager* sceneManager)
    : physicsEngine(engine), ui(uiInstance), window(win), sceneManager(sceneManager) {
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
            sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

            if (!UIClicked) {
                if (currentButton == Button::buttonType::clickToSpawn) {
					sceneManager->handleInput(InputAction::SpawnBall, mousePosition);
                }
                else if (currentButton == Button::buttonType::ballSpawner) {
                    sceneManager->handleInput(InputAction::SpawnPortal, mousePosition);
                }
                else if (currentButton == Button::buttonType::fastSpawn) {
                    sceneManager->handleInput(InputAction::FastSpawn, mousePosition); // You'll add this next
				}
            }
            else if (currentButton == Button::buttonType::ballPourer) {
                sceneManager->handleInput(InputAction::BallPourer, mousePosition);
            }
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			sceneManager->handleInput(InputAction::StopFastSpawn, sf::Vector2f(0.f, 0.f));
		}
    }
}
