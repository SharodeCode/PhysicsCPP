#include "Engine/Renderer.h"

Renderer::Renderer(sf::RenderWindow* win, UI* uiInstance) : window(win), ui(uiInstance) {}

void Renderer::render(const SceneManager& sceneManager, float deltaTime) {
    window->clear();
    //window->draw(sceneManager.getCurrentScene()->getGameObjects);

    const auto currentScene = sceneManager.getCurrentScene();
    if (!currentScene) return;

    for (const auto& object : currentScene->getGameObjects()) {
        if (const std::shared_ptr<RendererComponent> renderer = object->getComponent<RendererComponent>().lock()) {
            renderer->draw(*window);
        }
    }

    // Draw UI Panel
    if (auto panel = currentScene->getUIPanel()) {
        panel->draw(*window);
    }

    window->display();
}

void Renderer::initialize() {
    window->setFramerateLimit(FRAME_RATE);
}