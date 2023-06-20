#include "ParticleSystem.h"

void ParticleSystem::setEmitter(sf::Vector2f position) {
    m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed) {
    for (std::size_t i = 0; i < m_particles.size(); ++i) {
        // Update the particle's lifetime
        Particle& p = m_particles[i];
        p.lifetime -= elapsed;

        // If the particle is dead, reset it
        if (p.lifetime <= sf::Time::Zero) {
            resetParticle(i);
        }

        // Update the particle's position
        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        // Update the particle's transparency (alpha) based on its remaining lifetime
        float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
    }
}

void ParticleSystem::addParticles(unsigned int count) {
    m_particles.resize(m_particles.size() + count);
    m_vertices.resize(m_vertices.getVertexCount() + count);

    for (std::size_t i = m_particles.size() - count; i < m_particles.size(); ++i) {
        resetParticle(i);
    }
}