#include "Engine/Game.h"
#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Entities/Portal.h"
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>
#include <Engine/Game.h>

Game::Game()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PhysicsCPP"), physicsEngine(), ui(&window, &physicsEngine), // UI needs window first
    renderer(&window, &ui), // Renderer needs window & UI
    inputManager(physicsEngine, ui, window),
    subStepRate((1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f))
{
    window.setFramerateLimit(FRAME_RATE);
    physicsEngine.subStepCount = SUB_STEPS;
}



void Game::run() {
    sf::Clock clock;
    float accumulator = 0.0f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        processInput();
        update(deltaTime);
        render();
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
