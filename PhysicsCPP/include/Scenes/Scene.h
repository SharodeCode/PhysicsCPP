#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Entities/BaseEntity.h"
#include "Engine/InputManager.h"

enum class InputAction;

class PhysicsEngine;
class Renderer;
class UI;
class UIPanel;

class Scene {
protected:
    std::vector<std::shared_ptr<BaseEntity>> gameObjects;  // Physics-based objects

    PhysicsEngine* physicsEngine = nullptr;
    std::shared_ptr<UIPanel> uiPanel;
    UI* ui = nullptr;

public:
    virtual ~Scene() = default;

    void setSystems(PhysicsEngine* physics, UI* uiSystem) {
        physicsEngine = physics;
        ui = uiSystem;
    }

    const std::vector<std::shared_ptr<BaseEntity>>& getGameObjects() const {
        return gameObjects;
    }

    virtual void initialize() = 0;  // Setup the scene
    virtual void update(float deltaTime) = 0; // Update game objects

    std::shared_ptr<UIPanel> getUIPanel() { return uiPanel; }

    void addGameObject(std::shared_ptr<BaseEntity> object) {
        gameObjects.push_back(object);
    }

    virtual void onInput(InputAction action, sf::Vector2f spawnPosition) = 0;
};
