#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/PhysicsEngine.h"
#include "UI/UI.h"
#include "Scenes/SceneManager.h"


class SceneManager;

enum class InputAction {
    SpawnBall,
	SpawnPortal
};

class InputManager {
private:
    PhysicsEngine& physicsEngine;
    UI& ui;
    sf::RenderWindow& window;
    sf::Texture texture;
    Button::buttonType currentButton = Button::buttonType::mute;
    SceneManager* sceneManager;

public:
    InputManager(PhysicsEngine& engine, UI& uiInstance, sf::RenderWindow& win, SceneManager* sceneManager);
    void handleInput();
};
