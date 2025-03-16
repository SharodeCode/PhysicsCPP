#pragma once
#include <SFML/Graphics.hpp>

class Entity;  // Forward declaration

class Component {
protected:
    Entity* owner;  // The entity this component belongs to

public:
    virtual ~Component() = default;
    
    void setOwner(Entity* entity) { owner = entity; }
    Entity* getOwner() const { return owner; }

    virtual void update(float deltaTime) {}  // Ensure default implementation is provided

	virtual void draw(sf::RenderWindow& window) const {}  // Ensure default implementation is provided
};
