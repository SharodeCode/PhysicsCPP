#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "Scenes/Scene.h"


class SceneManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> currentScene;

public:
    SceneManager() = default;

    void addScene(const std::string& name, std::shared_ptr<Scene> scene) {
        scenes[name] = scene;
    }

    void setScene(const std::string& name, PhysicsEngine* physics, Renderer* render, UI* ui) {
        if (scenes.find(name) != scenes.end()) {
            currentScene = scenes[name];
            currentScene->setSystems(physics, render, ui);
            currentScene->initialize();
        }
    }

    void update(float deltaTime) {
        if (currentScene) {
            currentScene->update(deltaTime);
        }
    }

    void render(sf::RenderWindow& window) {
        if (currentScene) {
            currentScene->render(window);
        }

        if (auto panel = currentScene->getUIPanel()) {
            panel->draw(window);
        }
    }

    void handleInput(InputAction action, sf::Vector2f spawnPosition) {
        if (currentScene) {
            currentScene->onInput(action, spawnPosition);
        }
    }

    std::shared_ptr<Scene> getCurrentScene() const {
		return currentScene;
    }
};
