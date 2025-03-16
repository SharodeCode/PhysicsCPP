#include "Engine/Renderer.h"

Renderer::Renderer(sf::RenderWindow* win, UI* uiInstance) : window(win), ui(uiInstance) {}

void Renderer::render(const PhysicsEngine& engine, float deltaTime) {
    window->clear();
    window->draw(engine.getBoundaryShape());

    for (const auto& portal : engine.getPortals()) {
        portal.draw(*window);
    }

    for (const auto& ballPtr : engine.getBalls()) {
        if (ballPtr) {
            if (const RendererComponent* renderer = ballPtr->getRenderer()) {
                renderer->draw(*window);
            }
        }
    }

    ui->updateUI(deltaTime);

    window->display();
}
