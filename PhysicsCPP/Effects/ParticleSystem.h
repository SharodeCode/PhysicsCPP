#include "Objects/Ball.h"
#pragma once

struct Particle {
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Time lifetime;
};

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
    ParticleSystem(unsigned int count) :
        m_particles(count),
        m_vertices(sf::Points, count),
        m_lifetime(sf::seconds(3)),
        m_emitter(0, 0) {
    }

    void setEmitter(sf::Vector2f position);
    void update(sf::Time elapsed);
    void addParticles(unsigned int count);

private:
    void resetParticle(std::size_t index) {
        // Give the particle a random position around the emitter
        float angle = (std::rand() % 360) * 3.141592654f / 180.0f;
        float speed = (std::rand() % 50) + 50.0f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);
        m_vertices[index].position = m_emitter;
        m_vertices[index].color = sf::Color::Yellow;
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        states.texture = nullptr;
        target.draw(m_vertices, states);
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};

