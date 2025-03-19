#pragma once
#include <vector>
#include "Entities/Ball.h"
#include "Entities/Boundary.h"
#include "Entities/Spawner.h"
#include "Entities/Portal.h"
#include <SFML/Graphics.hpp>

class PhysicsEngine {
private:
    std::vector<std::shared_ptr<RigidbodyComponent>> rigidbodies;
    std::vector<Portal> portals;
    Spawner spawner;
    bool audioActive = false;

public:
    int subStepCount = 1;

    std::shared_ptr<Boundary> boundary;

    PhysicsEngine();
    void update(float subStepRate);
    void applyGravity();

    const std::vector<Portal>& getPortals() const;
    void toggleAudioActive();

    void addRigidbody(std::shared_ptr<RigidbodyComponent> rb) {
        rigidbodies.push_back(rb);
    }
};
