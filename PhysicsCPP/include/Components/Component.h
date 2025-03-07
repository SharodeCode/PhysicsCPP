#pragma once

class Entity;  // Forward declaration

class Component {
protected:
    Entity* owner;  // The entity this component belongs to

public:
    virtual ~Component() = default;
    
    void SetOwner(Entity* entity) { owner = entity; }
    Entity* GetOwner() const { return owner; }

    virtual void Update(float deltaTime) {}  // Ensure default implementation is provided
};
