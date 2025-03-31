#include "Engine/Renderer.h"
#include <Entities/BallBatchRenderer.h>

Renderer::Renderer(sf::RenderWindow* win, UI* uiInstance) : window(win), ui(uiInstance) {}

void Renderer::render(const SceneManager& sceneManager, float deltaTime) {
    window->clear();

    const auto currentScene = sceneManager.getCurrentScene();
    if (!currentScene) return;

    BallBatchRenderer ballRenderer;
    ballRenderer.begin();

    for (const auto& object : currentScene->getGameObjects()) {
        if (const auto* ball = dynamic_cast<Ball*>(object.get())) {
            ballRenderer.submit(*ball); // Add to batch
        }
        else {
            object->draw(*window); // Draw other entities normally
        }
    }

    ballRenderer.end();
    ballRenderer.draw(*window);
}

void Renderer::initialize() {
    window->setFramerateLimit(GameConfig::FRAME_RATE);
}