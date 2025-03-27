#include "Engine/PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
    : spawner(10.0f) {}

void PhysicsEngine::update(float subStepRate) {
    std::vector<std::future<void>> futures;

	// Update movement and gravity
    updateRigidBodies(subStepRate);

    // One thread: update + resolve boundary for each rigidbody
    futures.push_back(std::async(std::launch::async, [this, subStepRate]() {
        for (auto& rb : rigidbodies) {
            //CollisionSystem::resolveHollowCircleCollision(rb, boundary->getPosition(), boundary->getRadius());
        }
        }));

    for (auto& future : futures) {
        future.wait();
    }

    // Collision check after all motion and boundaries resolved
    CollisionSystem::checkBallCollisions(rigidbodies);


    for (auto& portal : portals) {
        portal.update(subStepRate);
    }
}

void PhysicsEngine::updateRigidBodies(float subStepRate) {

    for (auto rb : rigidbodies) {
        // Get current and previous position
        sf::Vector2f pos = rb->getOwner()->getPosition();
        sf::Vector2f prev = rb->getOwner()->getPositionLast();

        sf::Vector2f acceleration(0.f, GRAVITY * GameConfig::pixelsPerMeter);

		// Compute motion based on preious position
        sf::Vector2f motion = pos - prev;


        // Place a limit of fast movement
        float maxDist = 10.f;
        if (std::hypot(motion.x, motion.y) > maxDist)
            motion = (motion / std::hypot(motion.x, motion.y)) * maxDist;

		// Verlet position update based on motion and acceleration
        sf::Vector2f newPos = pos + motion + acceleration * (subStepRate * subStepRate);
        rb->getOwner()->setPositionLast(pos);
        rb->getOwner()->setPosition(newPos);
    }

}

const std::vector<Portal>& PhysicsEngine::getPortals() const
{
    return portals;
}

void PhysicsEngine::toggleAudioActive() {
    audioActive = !audioActive;
}


// This will be for impulse based physics.
void PhysicsEngine::applyGravity() {
    for (auto& rigidBody : rigidbodies) {
        if (rigidBody->getType() == RigidbodyComponent::Type::Dynamic) {
            rigidBody->applyForce(sf::Vector2f(0.0f, GRAVITY));
        }
    }
}