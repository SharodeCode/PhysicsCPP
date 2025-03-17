#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "Engine/Renderer.h"
#include "UI/UI.h"
#include "InputManager.h"

class Game {
private:
    sf::RenderWindow window; // Static window

    PhysicsEngine physicsEngine;
    UI ui;
    Renderer renderer;
    InputManager inputManager;

    bool running = true;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;
    const int FRAME_RATE = 60;
    const int SUB_STEPS = 8;
    float subStepRate;

public:
    Game();
    void run();
private:
    void processInput();
    void update(float deltaTime);
    void render();
};
