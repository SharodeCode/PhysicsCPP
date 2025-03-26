#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <future>
#include "Entities/Ball.h"
#include "Entities/Boundary.h"
#include "Entities/Spawner.h"
#include "Entities/Portal.h"
#include "Engine/CollisionSystem.h"
#include "PhysicsConstants.h"

class PhysicsEngine {
private:
    std::vector<std::shared_ptr<RigidbodyComponent>> rigidbodies;
    std::vector<Portal> portals;
    Spawner spawner;
    std::shared_ptr<Boundary> boundary;
    bool audioActive = false;
    void updateRigidBodies(float subStepRate);

public:
    int subStepCount;

    PhysicsEngine();
    void update(float subStepRate);
    void applyGravity();

    const std::vector<Portal>& getPortals() const;
    void toggleAudioActive();

    void addRigidbody(std::shared_ptr<RigidbodyComponent> rb) {
        rigidbodies.push_back(rb);
    }

	int getRigidbodyCount() const {
		return rigidbodies.size();
	}

	void setBoundary(std::shared_ptr<Boundary> boundary) {
		this->boundary = boundary;
	}
};
