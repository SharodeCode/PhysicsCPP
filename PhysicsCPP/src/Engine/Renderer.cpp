#include "Engine/Renderer.h"

Renderer::Renderer(sf::RenderWindow* win, UI* uiInstance) : window(win), ui(uiInstance) {}

void Renderer::render(const PhysicsEngine& engine, float deltaTime) {
    window->clear();
    window->draw(engine.getFrame());

    for (const auto& portal : engine.getPortals()) {
        window->draw(portal);
    }

    for (const auto& ballPtr : engine.getBalls()) {
        if (ballPtr) {
            if (const RendererComponent* renderer = ballPtr->GetRenderer()) {
                renderer->Draw(*window);
            }
        }
    }

    ui->updateUI(deltaTime);

    window->display();
}
