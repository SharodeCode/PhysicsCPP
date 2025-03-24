#include "Engine/PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
    : spawner(10.0f) {}


void PhysicsEngine::applyGravity() {
    for (auto& rigidBody : rigidbodies) {
        if (rigidBody->getType() == RigidbodyComponent::Type::Dynamic) {
            rigidBody->applyForce(sf::Vector2f(0.0f, GRAVITY));
        }
    }
}

void PhysicsEngine::update(float subStepRate) {
    std::vector<std::future<void>> futures;

    applyGravity();

    for (int i = 0; i < subStepCount; i++) {
        std::vector<std::future<void>> futures;

        // One thread: update + resolve boundary for each rigidbody
        futures.push_back(std::async(std::launch::async, [this, subStepRate]() {
            for (auto& rb : rigidbodies) {
                rb->update(subStepRate);
                CollisionSystem::resolveHollowCircleCollision(rb, boundary->getPosition(), boundary->getRadius());
            }
            }));

        for (auto& future : futures) {
            future.wait();
        }

        // Collision check after all motion and boundaries resolved
        CollisionSystem::checkBallCollisions(rigidbodies);
    }


    for (auto& portal : portals) {
        portal.update(subStepRate);
    }
}

const std::vector<Portal>& PhysicsEngine::getPortals() const
{
    return portals;
}

void PhysicsEngine::toggleAudioActive() {
    audioActive = !audioActive;
}