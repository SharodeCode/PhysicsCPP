#include "Entities/Boundary.h"

Boundary::Boundary(float radius, sf::Vector2f position) : radius(radius) {
    rigidbody = std::make_shared<RigidbodyComponent>(this, RigidbodyComponent::Type::Static, radius);
    addComponent<RendererComponent>(radius, sf::Color::Transparent, sf::Color::White, 10.0f, this);

    setPosition(position);               // Sets center position
    setPositionLast(position);          // Required for Verlet-style bodies
}

// Constructor for open box boundary
Boundary::Boundary(float width, float height, sf::Vector2f position)
    : boundaryType(BoundaryType::OpenBox), width(width), height(height) {

    sf::Vector2f center = position;

    auto left = std::make_shared<BoundaryWall>(
        sf::Vector2f(10.f, height),
        sf::Vector2f(-width / 2.f + 5.f, 0),
        center
    );
    auto right = std::make_shared<BoundaryWall>(
        sf::Vector2f(10.f, height),
        sf::Vector2f(width / 2.f - 5.f, 0),
        center
    );
    auto bottom = std::make_shared<BoundaryWall>(
        sf::Vector2f(width, 10.f),
        sf::Vector2f(0, height / 2.f - 5.f),
        center
    );

    walls = { left, right, bottom }; // store if needed

    // Register each wall as a game object
    for (auto& wall : walls) {
        gameObjects.push_back(wall); // OR pass them back to BallSpawnerScene to call addGameObject(wall)
    }

}

float Boundary::getRadius() const {
    return radius;
}

void Boundary::update(float deltaTime) {
    // Static boundary does not need to update
}

void Boundary::draw(sf::RenderWindow& window) const {
    if (auto renderer = getComponent<RendererComponent>().lock()) {
        renderer->draw(window);  // Let the renderer handle the drawing
    }

    if (boundaryType == BoundaryType::Circle) {
        window.draw(circle);
    }
    else if (boundaryType == BoundaryType::OpenBox) {
        for (const auto& wall : boxWalls) {
            window.draw(wall);
        }
    }
}
