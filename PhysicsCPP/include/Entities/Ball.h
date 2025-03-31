#pragma once
#include <SFML/Graphics.hpp>
#include "Components/RigidbodyComponent.h"
#include "Components/RendererComponent.h"
#include "PhysicsConstants.h"
#include "GameConfig.h"
#include <Engine/PhysicsDataPool.h>

class Ball : public BaseEntity {
private:
    float radius;
    std::shared_ptr<RigidbodyComponent> rigidbody;
    std::shared_ptr<RendererComponent> renderer;
	sf::Color color;

public:
    Ball(sf::Vector2f position, PhysicsDataPool* pool, int index);

    int physicsIndex = -1;

    PhysicsDataPool* physicsData = nullptr;

    sf::Vector2f getPosition() const {
        const auto& data = physicsData->get(physicsIndex);
        return { data.x, data.y };
    }

    void setPosition(const sf::Vector2f& pos) {
        auto& data = physicsData->get(physicsIndex);
        data.x = pos.x;
        data.y = pos.y;
    }

    sf::Vector2f getRenderPosition() const override {
        const auto& d = physicsData->get(physicsIndex);
        return { d.x, d.y };
    }

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) const override;

    std::shared_ptr<RendererComponent> getRenderer() const;
    std::shared_ptr<RigidbodyComponent> getRigidbody();

    void accelerate(sf::Vector2f a);
    void resetForces();

    float getRadius() const;
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& vel);
    float getGravity() const;

	sf::Color getColor() const {
		return color;
	}

	void setColor(const sf::Color& c) {
		color = c;
	}
};
