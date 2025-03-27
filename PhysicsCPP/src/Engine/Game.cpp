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
    }

}

void Game::update(float fixedDelta) {
	// Compute the rate that each supbstep should run, based on the fixed timestep.
    float subStepRate = fixedDelta / static_cast<float>(GameConfig::SUBSTEP_COUNT);

    for (int i = 0; i < GameConfig::SUBSTEP_COUNT; ++i) {
        sceneManager.update(subStepRate);         // spawn, control, etc.
        physicsEngine.update(subStepRate); // single substep
    }

    //physicsEngine.finalizeFrame(); // optional per-frame logic
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