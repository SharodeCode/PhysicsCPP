#pragma once
#include <SFML/Graphics.hpp>
#include "Components/Component.h"
#include <Components/RigidbodyComponent.h>
#include "Entities/BaseEntity.h"

class RendererComponent : public Component {
private:
    sf::CircleShape shape;
    sf::Sprite sprite;
    BaseEntity* owner;

public:
	//Constructor for filled circles (balls)
    RendererComponent(float radius, sf::Color color, BaseEntity* entity);

	// Constructor for textures (Portals)
    RendererComponent(const sf::Texture& texture, BaseEntity* entity);

    // Constructor for hollow circles (boundary)
    RendererComponent(float radius, sf::Color fillColor, sf::Color outlineColor, float outlineThickness, BaseEntity* entity);


    void update(float deltaTime) override {}
    void draw(sf::RenderWindow& window) const override;
};