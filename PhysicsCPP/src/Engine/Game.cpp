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

    while (window.isOpen()) {
        float rawDelta = clock.restart().asSeconds();
        float deltaTime = std::min(rawDelta, 1.f / 60.f);

        if(deltaTime != 0)
            subStepRate = (deltaTime) / GameConfig::SUBSTEP_COUNT;

        accumulator += deltaTime;

        processInput();

        sceneManager.update(deltaTime);

        while (accumulator >= subStepRate) {
            physicsEngine.update(subStepRate);
            accumulator -= subStepRate;
        }

        ui.update(rawDelta);

        render();
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