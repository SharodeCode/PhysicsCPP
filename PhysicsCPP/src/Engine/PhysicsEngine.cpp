#include "Engine/PhysicsEngine.h"
#include <iostream>

PhysicsEngine::PhysicsEngine()
    : spawner(10.0f) {}

void PhysicsEngine::update(float subStepRate) {
    std::vector<std::future<void>> futures;

	// Update movement and gravity
    updateRigidBodies(subStepRate);

    // One thread: update + resolve boundary for each rigidbody
    futures.push_back(std::async(std::launch::async, [this, subStepRate]() {
        for (auto& rb : rigidbodies) {
            for (const auto& boundary : boundaries) {
                boundary->resolve(rb);
            }
        }
        }));

    for (auto& future : futures) {
        future.wait();
    }

    // Collision check after all motion and boundaries resolved
    CollisionSystem::checkBallCollisions(dataPool);


    for (auto& portal : portals) {
        portal.update(subStepRate);
    }
}

void PhysicsEngine::updateRigidBodies(float subStepRate) {

    for (FlatBallData& ball : dataPool.ballData) {

        // Get current and previous position
        float x = ball.x;
        float y = ball.y;
        float lastX = ball.lastX;
        float lastY = ball.lastY;

        float accelY = GRAVITY * GameConfig::pixelsPerMeter;

        // Compute motion and clamp
        float motionX = x - lastX;
        float motionY = y - lastY;

        float distSq = motionX * motionX + motionY * motionY;
        if (distSq > 100.0f) { // 10^2
            float dist = std::sqrt(distSq);
            motionX = (motionX / dist) * 10.f;
            motionY = (motionY / dist) * 10.f;
        }

        // Verlet update
        float newX = x + motionX;
        float newY = y + motionY + accelY * (subStepRate * subStepRate);

        ball.lastX = x;
        ball.lastY = y;
        ball.x = newX;
        ball.y = newY;
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