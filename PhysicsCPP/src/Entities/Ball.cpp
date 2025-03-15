#include "Entities/Ball.h"
#include "PhysicsConstants.h"

Ball::Ball(sf::Vector2f position) : radius(10.0f), rigidbody(50.0f) {
    setPosition(position);
    position_last = position;

    // Generate a random color
    sf::Color randomColor(rand() % 256, rand() % 256, rand() % 256);

    addComponent<RigidbodyComponent>();
    addComponent<RendererComponent>(radius, randomColor);
    GetRenderer()->SetPosition(position);
}

void Ball::Update(float deltaTime) {
    sf::Vector2f displacement = getPosition() - position_last;
    position_last = getPosition();

    rigidbody.Update(deltaTime);
    setPosition(getPosition() + displacement + rigidbody.velocity * (deltaTime * deltaTime));

    if (RendererComponent* renderer = getComponent<RendererComponent>()) {
        renderer->SetPosition(getPosition());
    }

    if (RigidbodyComponent* rb = GetRigidbody()) {
        rb->Update(deltaTime);
        setPosition(getPosition() + rb->velocity * deltaTime);
    }
}

void Ball::accelerate(sf::Vector2f a) {
    rigidbody.ApplyForce(a * rigidbody.mass);
}

sf::Vector2f Ball::getVelocity() const {
    return rigidbody.velocity;
}

void Ball::setVelocity(const sf::Vector2f& vel) {
    rigidbody.velocity = vel;
}

float Ball::getGravity() const {
    return GRAVITY;
}

sf::Vector2f Ball::getPositionLast() const {
    return position_last;
}

void Ball::setPositionLast(const sf::Vector2f& pos) {
    position_last = pos;
}

float Ball::getRadius() const {
    return radius;
}

void Ball::Draw(sf::RenderWindow& window) const {
    if (const RendererComponent* renderer = GetRenderer()) {
        renderer->Draw(window);
    }
}

RigidbodyComponent* Ball::GetRigidbody() {
    return getComponent<RigidbodyComponent>();
}

RendererComponent* Ball::GetRenderer() const {
    return getComponent<RendererComponent>();
}
