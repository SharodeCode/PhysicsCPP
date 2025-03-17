#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "Engine/Renderer.h"
#include "UI/UI.h"
#include "InputManager.h"

class Game {
private:
    PhysicsEngine& physicsEngine;
    Renderer& renderer;
    UI& ui;
    InputManager& inputManager;
    sf::RenderWindow& window;

    bool running = true;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;
    const int FRAME_RATE = 60;
    const int SUB_STEPS = 8;
    float subStepRate;

public:
    Game(sf::RenderWindow& window, PhysicsEngine& physicsEngine, Renderer& renderer, UI& ui, InputManager& inputManager);
    void run();
private:
    void processInput();
    void update(float deltaTime);
    void render();
};
