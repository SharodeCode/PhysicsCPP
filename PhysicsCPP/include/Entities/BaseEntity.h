#pragma once
#include <vector>
#include <memory>
#include "Components/Component.h"

class BaseEntity {
protected:
    std::vector<std::unique_ptr<Component>> components;

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
    T* addComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = component.get();
        components.push_back(std::move(component));
        return ptr;
    }

    template <typename T>
    T* getComponent() const {
        for (const auto& component : components) {
            if (T* casted = dynamic_cast<T*>(component.get())) {
                return casted;
            }
        }
        return nullptr;
    }

    virtual void Update(float deltaTime) = 0;
    virtual void Draw(sf::RenderWindow& window) const = 0;
};
