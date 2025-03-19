#include "Engine/Game.h"

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsCPP"), physicsEngine(), ui(&window, &physicsEngine), // UI needs window first
    renderer(&window, &ui), // Renderer needs window & UI
    sceneManager(),
    inputManager(physicsEngine, ui, window, &sceneManager),
    subStepRate((1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f))
{
    window.setFramerateLimit(FRAME_RATE);
    physicsEngine.subStepCount = SUB_STEPS;

    GameConfig::setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    sceneManager.addScene("Ball Spawner", std::make_shared<BallSpawnerScene>());
    sceneManager.setScene("Ball Spawner", &physicsEngine, &renderer, &ui);  // Start at Gameplay
}

void Game::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        processInput();

        sceneManager.update(deltaTime);
		physicsEngine.update(deltaTime);

        render();
    }

}

void Game::processInput() {
    inputManager.handleInput();
}

void Game::render() {
    renderer.render(sceneManager, 1.0f / 120.0f);
}