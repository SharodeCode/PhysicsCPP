#pragma once
#include "Scene.h"
#include "Entities/Ball.h"
#include "UI/Button.h"
#include "GameConfig.h"

class BallSpawnerScene : public Scene {
private:
    std::vector<std::shared_ptr<Ball>> balls;
    std::shared_ptr<Button> spawnButton;
    std::shared_ptr<Boundary> boundary;

    sf::Vector2f fastSpawnOrigin;
    bool fastSpawning = false;
    float fastSpawnTimer = 0.f;

public:
    void initialize() override {
		initialiseUI();
		boundary = std::make_shared<Boundary>(250.f, sf::Vector2f(100.f, 400.f));
		addGameObject(boundary);
		physicsEngine->setBoundary(boundary);
		//physicsEngine->addRigidbody(boundary->getRigidbody());

		spawnBalls(50);
    }

    void initialiseUI(){
		uiPanel = std::make_shared<UIPanel>();
        const float buttonWidth = 200.f;
        const float buttonHeight = 50.f;
        const float buttonGap = 10.f;

        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::mute, (800 - 200.f), 0.f, buttonWidth, buttonHeight, "Mute", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::ballSpawner, (800 - 200.f), (buttonHeight + buttonGap), buttonWidth, buttonHeight, "Ball Spawner", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::clickToSpawn, (800 - 200.f), ((2 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Click to Spawn", *uiPanel));
		uiPanel->addElement(std::make_shared<Button>(Button::buttonType::fastSpawn, (800 - 200.f), ((3 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Fast Spawn", *uiPanel));

        

		ui->m_UIPanel = uiPanel;

        ui->elements.push_back(uiPanel);
    }

    void update(float deltaTime) override {
        if (fastSpawning) {
            fastSpawnTimer += deltaTime;
            const float spawnInterval = 0.01f;  // fast!

            while (fastSpawnTimer >= spawnInterval) {
                fastSpawnTimer -= spawnInterval;

                float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159f;
                float dist = static_cast<float>(std::rand()) / RAND_MAX * 10.f;

                sf::Vector2f offset(std::cos(angle) * dist, std::sin(angle) * dist);
                spawnBall(fastSpawnOrigin + offset);
            }
        }

        
    }

    void onInput(InputAction action, sf::Vector2f spawnPosition) {
        if (action == InputAction::SpawnBall) {
            spawnBall(spawnPosition);
        }
        else if (action == InputAction::FastSpawn) {
            fastSpawnOrigin = spawnPosition;
            fastSpawning = true;
            fastSpawnTimer = 0.f;
		}
		else if (action == InputAction::StopFastSpawn) {
			fastSpawning = false;
		}
    }

	void spawnBall(sf::Vector2f spawnPosition) {
		auto ball = std::make_shared<Ball>(spawnPosition);
		addGameObject(ball);
		physicsEngine->addRigidbody(ball->getRigidbody());
	}

    void spawnBalls(int count) {
        const float ballRadius = 10.0f;
        const float spacing = ballRadius * 2.2f;  // Slightly larger than diameter to prevent overlap
        const int maxRetries = 10; // Avoid infinite loops if placement is difficult

        std::vector<sf::Vector2f> positions; // Track placed positions

        for (int i = 0; i < count; ++i) {
            int retries = 0;
            bool placed = false;

            while (!placed && retries < maxRetries) {
                // Generate a random position within the window but inside the boundary
                float x = static_cast<float>(rand() % (GameConfig::WINDOW_WIDTH - 2 * (int)ballRadius) + ballRadius);
                float y = static_cast<float>(rand() % (GameConfig::WINDOW_HEIGHT - 2 * (int)ballRadius) + ballRadius);
                sf::Vector2f newPos(x, y);

                // Check if the position overlaps with existing balls
                bool valid = true;
                for (const auto& pos : positions) {
                    if (std::hypot(pos.x - newPos.x, pos.y - newPos.y) < spacing) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
					spawnBall(newPos);
                    positions.push_back(newPos);
                    placed = true;
                }
                else {
                    ++retries;
                }
            }
        }
    }

};
