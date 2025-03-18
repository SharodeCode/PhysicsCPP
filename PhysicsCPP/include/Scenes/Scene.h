#pragma once
#include <vector>
#include <memory>
#include "Entities/BaseEntity.h"  // Game objects
#include <SFML/Graphics.hpp>

class Scene {
protected:
    std::vector<std::shared_ptr<BaseEntity>> gameObjects;  // Physics-based objects

    PhysicsEngine* physicsEngine = nullptr;
    Renderer* renderer = nullptr;
    std::shared_ptr<UIPanel> uiPanel;
    UI* ui = nullptr;

public:
    virtual ~Scene() = default;

    void setSystems(PhysicsEngine* physics, Renderer* render, UI* uiSystem) {
        physicsEngine = physics;
        renderer = render;
        ui = uiSystem;
    }
    virtual void initialize() = 0;  // Setup the scene
    virtual void update(float deltaTime) = 0; // Update game objects
    virtual void render(sf::RenderWindow& window) = 0; // Draw everything

    void addGameObject(std::shared_ptr<BaseEntity> object) {
        gameObjects.push_back(object);
    }
};
