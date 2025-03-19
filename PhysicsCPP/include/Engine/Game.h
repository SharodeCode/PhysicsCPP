#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "Engine/Renderer.h"
#include "UI/UI.h"
#include "InputManager.h"
#include "Scenes/SceneManager.h"
#include "Entities/Ball.h"
#include "Entities/Portal.h"
#include <GameConfig.h>
#include <Scenes/BallSpawnerScene.h>

class Game {
private:
    sf::RenderWindow window;
    PhysicsEngine physicsEngine;
    UI ui;
    Renderer renderer;
    SceneManager sceneManager;
    InputManager inputManager;


    std::shared_ptr<UIPanel> panel;

    bool running = true;
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 800;
    const int FRAME_RATE = 120;
    const int SUB_STEPS = 8;
    float subStepRate;

public:
    Game();
    void run();

    PhysicsEngine& getPhysicsEngine() { return physicsEngine; }
    Renderer& getRenderer() { return renderer; }

    void render();

private:
    void processInput();
};
