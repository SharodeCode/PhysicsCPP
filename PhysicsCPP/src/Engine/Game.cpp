#include "Engine/Game.h"
#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Entities/Portal.h"
#include <Engine/Renderer.h>
#include <Engine/InputManager.h>
#include <Engine/Game.h>


sf::RenderWindow Game::window(sf::VideoMode(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT), "PhysicsCPP");

Game::Game()
    : physicsEngine(),
    ui(&window, &physicsEngine),
    renderer(&window, &ui),
    inputManager(physicsEngine, ui, window),
    subStepRate((1.0f / FRAME_RATE) / (SUB_STEPS * 0.5f))
{
	physicsEngine.subStepCount = SUB_STEPS;
    window.setFramerateLimit(FRAME_RATE);
}


void Game::run() {

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
