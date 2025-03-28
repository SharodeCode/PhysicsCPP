#include "Engine/Game.h"


Game::Game()
    : window(sf::VideoMode(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT), "PhysicsCPP"), physicsEngine(), ui(&window, &physicsEngine), // UI needs window first
    renderer(&window, &ui), // Renderer needs window & UI
    sceneManager(),
    inputManager(physicsEngine, ui, window, &sceneManager),
    subStepRate((1.0f / GameConfig::FRAME_RATE) / GameConfig::SUBSTEP_COUNT)
{
    window.setFramerateLimit(GameConfig::FRAME_RATE);
    physicsEngine.subStepCount = GameConfig::SUBSTEP_COUNT;

    GameConfig::setWindowSize(GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT);
    
    sceneManager.addScene("Ball Spawner", std::make_shared<BallSpawnerScene>());
    sceneManager.setScene("Ball Spawner", &physicsEngine, &ui);  // Start at Gameplay
}

void Game::run() {
    sf::Clock clock;
    float accumulator = 0.0f;
    float startTime = 0.0f;

    std::deque<float> recentFrames;
    std::unordered_set<int> printedBallBenchmarks;

	// Stable timestep loop.
    const float fixedDelta = 1.0f / GameConfig::FRAME_RATE;

    while (window.isOpen()) {
        // Measure real-world time since last frame
        float rawDelta = clock.restart().asSeconds();

        // Clamp large frame spikes (e.g., due to window dragging or pausing)
        float deltaTime = std::min(rawDelta, 1.f / GameConfig::FRAME_RATE);

        accumulator += deltaTime;

        // Handle player input events
        processInput();

        // Run simulation in fixed time steps to maintain determinism
        while (accumulator >= fixedDelta) {
			update(fixedDelta);
            accumulator -= fixedDelta;
        }

        // Update UI using real delta time (for FPS display)
        ui.update(rawDelta);

        // Render the scene and UI to the window
        render();


		// Benchmarking logic
        if (GameConfig::ENABLE_BENCHMARKING) {
            int ballCount = physicsEngine.getRigidbodyCount();

            if (ballCount == 0 || ballCount == 10 || ballCount == 50 || ballCount == 100 ||
                ballCount == 250 || ballCount == 500 || ballCount == 600 || ballCount == 800 || ballCount == 1000
                || ballCount == 1100 || ballCount == 1200 || ballCount == 1300 || ballCount == 1400 || ballCount == 1500
                || ballCount == 1600 || ballCount == 1700 || ballCount == 1800 || ballCount == 1900 || ballCount == 2000) {

                if (!printedBallBenchmarks.contains(ballCount)) {
                    std::cout << "| " << ballCount
                        << " | " << (totalSubstepTime / GameConfig::SUBSTEP_COUNT)
                        << " | " << 1.0f / rawDelta
                        << " | " << CollisionSystem::collisionChecks
                        << " | " << CollisionSystem::collisionsResolved
                        << " | " << totalSubstepTime
                        << " | " << physicsTime
                        << " |\n";
                    printedBallBenchmarks.insert(ballCount);
                }
            }

            CollisionSystem::collisionsResolved = 0;
            CollisionSystem::collisionChecks = 0;


            recentFrames.push_back(rawDelta);
            if (recentFrames.size() > sampleWindow)
                recentFrames.pop_front();

            float avgFrameTime = 0.f;
            for (float t : recentFrames) avgFrameTime += t;
            avgFrameTime /= recentFrames.size();

            float averageFPS = 1.f / avgFrameTime;

            if (!benchmarkTriggered && recentFrames.size() == sampleWindow && averageFPS < 60.f) {
                int activeBallCount = physicsEngine.getRigidbodyCount();
                std::cout << "[Benchmark] FPS dropped below 60 with " << activeBallCount << " balls.\n";
                benchmarkTriggered = true;
            }
        }

    }

}

void Game::update(float fixedDelta) {
	// Compute the rate that each supbstep should run, based on the fixed timestep.
    float subStepRate = fixedDelta / static_cast<float>(GameConfig::SUBSTEP_COUNT);

	totalSubstepTime = 0.f; // BENCHMARKING: Time substeps

    for (int i = 0; i < GameConfig::SUBSTEP_COUNT; ++i) {
        sf::Clock stepTimer;
        sceneManager.update(subStepRate); // spawn, control, etc.

		physicsTimer.restart(); // BENCHMARKING: Time physics update
        physicsEngine.update(subStepRate); // single substep
		physicsTime = physicsTimer.getElapsedTime().asMicroseconds(); // BENCHMARKING: Time physics update

        totalSubstepTime += stepTimer.getElapsedTime().asMicroseconds();  // BENCHMARKING: Time substeps
    }
}

void Game::processInput() {
    inputManager.handleInput();
}

void Game::render() {
    renderer.render(sceneManager, 1.0f / GameConfig::FRAME_RATE);

    // UI should be drawn last, after scene rendering
    ui.render(window);

    // Now call display at the very end
    window.display();
}