#include "Entities/BallBatchRenderer.h"
#include <cmath>

BallBatchRenderer::BallBatchRenderer(int segments)
    : segments(segments), vertexArray(sf::Triangles) {}

void BallBatchRenderer::begin() {
    vertexArray.clear();
}

void BallBatchRenderer::submit(const Ball& ball) {
    const sf::Vector2f center = ball.getPosition();
    const float radius = ball.getRadius();
    const sf::Color color = ball.getColor();

    float angleStep = 2.f * 3.14159265f / segments;

    // Center vertex
    sf::Vertex centerVertex(center, color);

    for (int i = 0; i < segments; ++i) {
        float angle1 = i * angleStep;
        float angle2 = (i + 1) * angleStep;

        sf::Vector2f p1 = center + sf::Vector2f(std::cos(angle1), std::sin(angle1)) * radius;
        sf::Vector2f p2 = center + sf::Vector2f(std::cos(angle2), std::sin(angle2)) * radius;

        vertexArray.append(centerVertex);
        vertexArray.append(sf::Vertex(p1, color));
        vertexArray.append(sf::Vertex(p2, color));
    }
}

void BallBatchRenderer::end() {
    
}

void BallBatchRenderer::draw(sf::RenderWindow& window) const {
    window.draw(vertexArray);
}
