#pragma once
#include <vector>
#include <memory>
#include "Components/Component.h"

class BaseEntity {
protected:
    std::vector<std::shared_ptr<Component>> components;
    sf::Vector2f position;
    sf::Vector2f positionLast;

public:
    virtual ~BaseEntity() = default;

    // Add a constructor
    BaseEntity() {}

    // Prevent copying
    BaseEntity(const BaseEntity&) = delete;
    BaseEntity& operator=(const BaseEntity&) = delete;

    // Allow moving
    BaseEntity(BaseEntity&&) = default;
    BaseEntity& operator=(BaseEntity&&) = default;

    template <typename T, typename... Args>
    std::shared_ptr<T> addComponent(Args&&... args) {
        auto component = std::make_shared<T>(std::forward<Args>(args)...);
        components.push_back(component);
        return component;
    }

    template <typename T>
    std::weak_ptr<T> getComponent() const {
        for (const auto& component : components) {
            if (auto casted = std::dynamic_pointer_cast<T>(component)) {
                return casted;
            }
        }
        return std::weak_ptr<T>{};
    }

    virtual void update(float deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) const = 0;

    void setPosition(const sf::Vector2f& newPos) { position = newPos; }
    sf::Vector2f getPosition() const { return position; }

    void setPositionLast(const sf::Vector2f& newPos) { positionLast = newPos; }
    sf::Vector2f getPositionLast() const { return positionLast; }
};
