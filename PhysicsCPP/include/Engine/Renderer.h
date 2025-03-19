#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Portal.h"
#include "Engine/PhysicsEngine.h"
#include <UI/UI.h>
#include <Scenes/SceneManager.h>

class Renderer {
private:
    sf::RenderWindow* window;
    UI* ui;

    const int FRAME_RATE = 60;

public:
    Renderer(sf::RenderWindow* win, UI* uiInstance);

    void initialize();
    void render(const SceneManager& sceneManager, float deltaTime);
};
