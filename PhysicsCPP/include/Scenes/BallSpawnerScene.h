#pragma once
#include "Scene.h"
#include "Entities/Ball.h"
#include "UI/Button.h"

class BallSpawnerScene : public Scene {
private:
    std::vector<std::shared_ptr<Ball>> balls;
    std::shared_ptr<Button> spawnButton;
    std::shared_ptr<Boundary> boundary;

public:
    void initialize() override {
		initialiseUI();
		boundary = std::make_shared<Boundary>(250.f, sf::Vector2f(100.f, 400.f));
		addGameObject(boundary);
		physicsEngine->boundary = boundary;
		//physicsEngine->addRigidbody(boundary->getRigidbody());
    }

    void initialiseUI(){
		uiPanel = std::make_shared<UIPanel>();
        const float buttonWidth = 200.f;
        const float buttonHeight = 50.f;
        const float buttonGap = 10.f;

        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::mute, (800 - 200.f), 0.f, buttonWidth, buttonHeight, "Mute", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::ballSpawner, (800 - 200.f), (buttonHeight + buttonGap), buttonWidth, buttonHeight, "Ball Spawner", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::clickToSpawn, (800 - 200.f), ((2 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Click to Spawn", *uiPanel));
        

		ui->m_UIPanel = uiPanel;

        ui->elements.push_back(uiPanel);
    }

    void update(float deltaTime) override {
        physicsEngine->update(0.0008333f);
    }

    void render(sf::RenderWindow& window) override {
        if (uiPanel) {
            uiPanel->draw(window);
        }
    }

    void onInput(InputAction action, sf::Vector2f spawnPosition) {
        if (action == InputAction::SpawnBall) {
            auto ball = std::make_shared<Ball>(spawnPosition);
            addGameObject(ball);
            physicsEngine->addRigidbody(ball->getRigidbody());
        }
    }
};
