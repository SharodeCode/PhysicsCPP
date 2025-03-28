#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/BaseEntity.h"
#include "Components/RigidbodyComponent.h"
#include "Components/RendererComponent.h"
#include "Entities/BoundaryWall.h"

class Boundary : public BaseEntity {

public:
    enum class BoundaryType {
        Circle,
        OpenBox
    };

private:
    sf::CircleShape circle;
    std::vector<sf::RectangleShape> boxWalls; // For the U-shaped box (4 walls, top missing)

    float radius; // For circle boundary
    float width, height; // For box boundary

    std::vector<std::shared_ptr<BoundaryWall>> walls;
    std::vector<std::shared_ptr<BaseEntity>> gameObjects;

    sf::CircleShape frame;
    std::shared_ptr<RigidbodyComponent> rigidbody;

public:
    BoundaryType boundaryType;

    Boundary(float radius, sf::Vector2f position);
    Boundary(float width, float height, sf::Vector2f position);

    float getRadius() const;

    std::shared_ptr<RigidbodyComponent> getRigidbody() const { return rigidbody; }

    // Implement required functions from BaseEntity
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;
};
