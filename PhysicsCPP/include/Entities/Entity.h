#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>

class Component;  // Forward declaration

class Entity {
private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

public:
    virtual ~Entity() = default;

    template <typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        auto component = std::make_unique<T>(std::forward<Args>(args)...);
        component->SetOwner(this);
        T* rawPtr = component.get();
        components[std::type_index(typeid(T))] = std::move(component);
        return rawPtr;
    }



    template <typename T>
    T* GetComponent() {
        auto it = components.find(std::type_index(typeid(T)));
        return it != components.end() ? static_cast<T*>(it->second.get()) : nullptr;
    }
};
