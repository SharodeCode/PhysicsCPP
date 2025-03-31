#pragma once
#include "Scene.h"
#include "Entities/Ball.h"
#include "Entities/Boundaries/CircleBoundary.h"
#include "Entities/Boundaries/OpenBoxBoundary.h"
#include "UI/Button.h"
#include "GameConfig.h"

class BallSpawnerScene : public Scene {
private:
    std::vector<std::shared_ptr<Ball>> balls;
    std::shared_ptr<Button> spawnButton;

    sf::Vector2f fastSpawnOrigin;
    bool fastSpawning = false;
    float fastSpawnTimer = 0.f;

    // Ball Pourer
	bool ballPourerToggle = false;
    float ballPourerSpawnTimer = 0.f;
    int ballPourCount = 5;


    sf::FloatRect openBoxBoundary;


public:
    void initialize() override {
        initialiseUI();

        CircleBoundaryInitialise();

        spawnBalls(0);
    }


    void CircleBoundaryInitialise() {
        sf::Vector2f center(400.f, 400.f);
        float radius = 250.f;

        auto circle = std::make_shared<CircleBoundary>(center, radius);
        physicsEngine->addBoundary(circle);
        addGameObject(circle);  // Optional for rendering
    }

    void BoxBoundaryInitialise() {
        const float wallThickness = 10.f;
        const float boxWidth = 600.f;
        const float boxHeight = 400.f;
        sf::Vector2f boxCenter(400.f, 400.f);

        auto box = std::make_shared<OpenBoxBoundary>(boxCenter, boxWidth, boxHeight, wallThickness);
        physicsEngine->addBoundary(box);
        addGameObject(box);

        for (const auto& wall : box->getWalls()) {
            addGameObject(wall);
        }

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
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::ballPourer, (800 - 200.f), ((4 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Ball Pourer", *uiPanel));
        
		ui->m_UIPanel = uiPanel;

        ui->elements.push_back(uiPanel);
    }

    void update(float deltaTime) override {

        if (fastSpawning) {
			fastSpawner(deltaTime);
        }

		if (ballPourerToggle) {
			ballPourer(deltaTime);
		}

    }

    void fastSpawner(float deltaTime) {
        fastSpawnTimer += deltaTime;
        const float spawnInterval = 0.01f;  // fast!

        while (fastSpawnTimer >= spawnInterval) {
            fastSpawnTimer -= spawnInterval;

            float angle = static_cast<float>(std::rand()) / RAND_MAX * 2.f * 3.14159f;
            float dist = static_cast<float>(std::rand()) / RAND_MAX * 10.f;

            sf::Vector2f offset = sf::Vector2f(cos(angle), sin(angle)) * (GameConfig::BALL_RADIUS * 2.1f);
            spawnBall(fastSpawnOrigin + offset);
        }
    }

    void ballPourer(float deltaTime) {
        sf::Vector2f hoseOrigin(250.f, 250.f); // starting point
        sf::Vector2f hoseVelocity(300.f, -50.f); // in pixels per second

        ballPourerSpawnTimer += deltaTime;
        if (ballPourerSpawnTimer >= 0.04f) { // tweak this for smoother flow
            ballPourerSpawnTimer = 0.f;

            for (int i = 0; i < ballPourCount; ++i) {
                sf::Vector2f offset(hoseOrigin.x, hoseOrigin.y + i * 10.f); //vertical spread

                // Inject physics
                int index = physicsEngine->dataPool.allocateBall(
                    hoseOrigin.x,
                    hoseOrigin.y + i * 10.f,
                    GameConfig::BALL_RADIUS
                );

                auto ball = std::make_shared<Ball>(offset, &physicsEngine->dataPool, index);

                sf::Vector2f verletOffset = hoseVelocity * deltaTime;
                auto& data = ball->physicsData->get(ball->physicsIndex);
                data.lastX = (offset - verletOffset).x;
                data.lastY = (offset - verletOffset).y;

                addGameObject(ball);
                physicsEngine->addRigidbody(ball->getRigidbody());
                balls.push_back(ball);
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
        else if (action == InputAction::BallPourer) {
            ballPourerToggle = !ballPourerToggle;
        }
    }

	void spawnBall(sf::Vector2f spawnPosition) {
        if (isOverlapping(spawnPosition, GameConfig::BALL_RADIUS)) return;

        // Inject physics
        int index = physicsEngine->dataPool.allocateBall(
            spawnPosition.x,
            spawnPosition.y,
            GameConfig::BALL_RADIUS
        );

        auto ball = std::make_shared<Ball>(spawnPosition, &physicsEngine->dataPool, index);

        auto& data = ball->physicsData->get(ball->physicsIndex);
        data.lastX = spawnPosition.x;
        data.lastY = spawnPosition.y;

        addGameObject(ball);
        physicsEngine->addRigidbody(ball->getRigidbody());
        balls.push_back(ball);  // Needed for isOverlapping
	}

    bool isOverlapping(const sf::Vector2f& pos, float radius) {
        for (const auto& ball : balls) {
            sf::Vector2f otherPos = ball->getPosition();
            float dist = std::hypot(pos.x - otherPos.x, pos.y - otherPos.y);
            if (dist < radius * 2.0f) {
                return true;
            }
        }
        return false;
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
