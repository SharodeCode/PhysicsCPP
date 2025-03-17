#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "Engine/Renderer.h"
#include "UI/UI.h"
#include "InputManager.h"

class Game {
private:
    static sf::RenderWindow window;
    PhysicsEngine physicsEngine;
    Renderer renderer;
    UI ui;
    InputManager inputManager;

    bool running = true;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;
    const int FRAME_RATE = 60;
    float subStepRate;
    const int SUB_STEPS = 8;

public:
    Game();
    void run();
private:
    void processInput();
    void update(float deltaTime);
    void render();
};
