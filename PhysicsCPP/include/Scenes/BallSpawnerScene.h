#pragma once
#include <fstream>
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
    int ballPourCount = 10;


    sf::FloatRect openBoxBoundary;

    std::vector<sf::Color> savedColors;
    size_t colorIndex = 0;


public:
    void initialize() override {
        initialiseUI();

        CircleBoundaryInitialise();

        spawnBalls(0);

		// Try and load colours from file
        std::ifstream in("Media/colors.txt");
        if (!in) {
            std::cerr << "Failed to open color file for reading!\n";
            return;
        }

        savedColors.clear();
        colorIndex = 0;

        int r, g, b;
        while (in >> r >> g >> b) {
            savedColors.emplace_back(sf::Color(r, g, b));
        }

    }


    void CircleBoundaryInitialise() {
        sf::Vector2f center(900.f, 450.f);
        float radius = 400.f;

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

        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::mute, (GameConfig::WINDOW_WIDTH - 200.f), 0.f, buttonWidth, buttonHeight, "Mute", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::ballSpawner, (GameConfig::WINDOW_WIDTH - 200.f), (buttonHeight + buttonGap), buttonWidth, buttonHeight, "Ball Spawner", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::clickToSpawn, (GameConfig::WINDOW_WIDTH - 200.f), ((2 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Click to Spawn", *uiPanel));
		uiPanel->addElement(std::make_shared<Button>(Button::buttonType::fastSpawn, (GameConfig::WINDOW_WIDTH - 200.f), ((3 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Fast Spawn", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::ballPourer, (GameConfig::WINDOW_WIDTH - 200.f), ((4 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Ball Pourer", *uiPanel));
        uiPanel->addElement(std::make_shared<Button>(Button::buttonType::coloriseBalls, (GameConfig::WINDOW_WIDTH - 200.f), ((5 * (buttonHeight + buttonGap))), buttonWidth, buttonHeight, "Colorise Balls", *uiPanel));
        
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

        if (physicsEngine->getRigidbodyCount() > 11600)
            return;

        sf::Vector2f hoseOrigin(800.f, 100.f); // starting point
        sf::Vector2f hoseVelocity(300.f, -50.f); // in pixels per second

        ballPourerSpawnTimer += deltaTime;
        if (ballPourerSpawnTimer >= 0.03f) { // tweak this for smoother flow
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

                // Use saved colours to colour balls to image
                if (!savedColors.empty()) {
                    ball->setColor(savedColors[colorIndex % savedColors.size()]);
                    ++colorIndex;
                }

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
		else if (action == InputAction::ColoriseBalls) {
			colouriseBallsAction();
		}
    }

	// Colourise balls based on an image
    void colouriseBallsAction() {

        // Load the image
        sf::Image image;
        if (!image.loadFromFile("./Media/Fonts/image_2.png")) {
            std::cerr << "Failed to load image\n";
        }

        // Colourise current balls
        sf::Vector2u imageSize = image.getSize();
        float scaleX = static_cast<float>(imageSize.x) / 800.f;
        float scaleY = static_cast<float>(imageSize.y) / 800.f;

        for (const auto& obj : gameObjects) {
            if (auto* ball = dynamic_cast<Ball*>(obj.get())) {
                sf::Vector2f pos = ball->getRenderPosition();

                float boxLeft = 900.f - 400.f;
                float boxTop = 450.f - 400.f;

                float relativeX = pos.x - boxLeft;
                float relativeY = pos.y - boxTop;

                int px = static_cast<int>(relativeX * scaleX);
                int py = static_cast<int>(relativeY * scaleY);

                if (px >= 0 && px < static_cast<int>(imageSize.x) &&
                    py >= 0 && py < static_cast<int>(imageSize.y)) {
                    ball->setColor(image.getPixel(px, py));
                }
            }
        }

        // Save ball colours to data structure
        savedColors.clear();
        for (const auto& obj : gameObjects) {
            if (auto* ball = dynamic_cast<Ball*>(obj.get())) {
                savedColors.push_back(ball->getColor());
            }
        }
        colorIndex = 0;

        // Save ball colours to output stream
        std::ofstream out("Media/colors.txt");
        if (!out) {
            std::cerr << "Failed to open color file for writing!\n";
            return;
        }

        for (const auto& color : savedColors) {
            out << static_cast<int>(color.r) << " "
                << static_cast<int>(color.g) << " "
                << static_cast<int>(color.b) << "\n";
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
