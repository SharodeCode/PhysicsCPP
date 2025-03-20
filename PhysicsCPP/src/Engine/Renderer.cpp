#include "Engine/Renderer.h"

Renderer::Renderer(sf::RenderWindow* win, UI* uiInstance) : window(win), ui(uiInstance) {}

void Renderer::render(const SceneManager& sceneManager, float deltaTime) {
    window->clear();

    const auto currentScene = sceneManager.getCurrentScene();
    if (!currentScene) return;

    for (const auto& object : currentScene->getGameObjects()) {
        if (const std::shared_ptr<RendererComponent> renderer = object->getComponent<RendererComponent>().lock()) {
            renderer->draw(*window);
        }
    }
}

void Renderer::initialize() {
    window->setFramerateLimit(GameConfig::FRAME_RATE);
}