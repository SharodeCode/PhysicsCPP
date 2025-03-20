#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "Engine/Renderer.h"
#include "UI/UI.h"
#include "InputManager.h"
#include "Scenes/SceneManager.h"
#include "GameConfig.h"
#include "Scenes/BallSpawnerScene.h"

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
