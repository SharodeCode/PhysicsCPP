#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Portal.h"
#include "Engine/PhysicsEngine.h"
#include <UI/UI.h>

class Renderer {
private:
    sf::RenderWindow* window;
    UI* ui;

public:
    Renderer(sf::RenderWindow* win, UI* uiInstance);

    void render(const PhysicsEngine& engine, float deltaTime);
};
