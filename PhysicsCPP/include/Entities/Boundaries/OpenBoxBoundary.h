#pragma once
#include <SFML/System.hpp>
#include "BaseBoundary.h"
#include "Entities/BoundaryWall.h"
#include "Components/RigidbodyComponent.h"

class OpenBoxBoundary : public BaseEntity, public BaseBoundary {
public:
    OpenBoxBoundary(const sf::Vector2f& center, float width, float height, float thickness);

    void resolve(std::shared_ptr<RigidbodyComponent>& rb) const override;
    void update(float) override {}
    void draw(sf::RenderWindow&) const override;

    const std::vector<std::shared_ptr<BoundaryWall>>& getWalls() const { return walls; }

private:
    std::vector<std::shared_ptr<BoundaryWall>> walls;
};
