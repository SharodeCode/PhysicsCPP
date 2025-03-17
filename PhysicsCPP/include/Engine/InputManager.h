#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"

class InputManager {
private:
    PhysicsEngine& physicsEngine;
    UI& ui;
    sf::RenderWindow& window;
    sf::Texture texture; // For portals
    Button::buttonType currentButton = Button::buttonType::mute;

public:
    InputManager(PhysicsEngine& engine, UI& uiInstance, sf::RenderWindow& win);
    void handleInput();
};
