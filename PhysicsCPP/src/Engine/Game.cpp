#include "Engine/Game.h"
#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Entities/Portal.h"
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>
#include <Engine/Game.h>
#include <GameConfig.h>
#include <Scenes/BallSpawnerScene.h>

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsCPP"), physicsEngine(), ui(&window, &physicsEngine), // UI needs window first
    renderer(&window, &ui), // Renderer needs window & UI
    inputManager(physicsEngine, ui, window),
    sceneManager(),
    subStepRate((1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f))
{
    window.setFramerateLimit(FRAME_RATE);
    physicsEngine.subStepCount = SUB_STEPS;

    GameConfig::setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    sceneManager.addScene("Ball Spawner", std::make_shared<BallSpawnerScene>());
    sceneManager.setScene("Ball Spawner", &physicsEngine, &renderer, &ui);  // Start at Gameplay
}

void Game::InitialiseUI() {
    panel = std::make_shared<UIPanel>();


    ui.m_UIPanel = panel;

    ui.elements.push_back(panel);
}

void Game::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        processInput();

        sceneManager.update(deltaTime);
        sceneManager.render(window);
    }

}

void Game::processInput() {
    inputManager.handleInput();
}

void Game::update(float deltaTime) {
    physicsEngine.update(subStepRate);
}

void Game::render() {
    renderer.render(physicsEngine, 1.0f / FRAME_RATE);
}
