#pragma once
#include <SFML/Graphics.hpp>
#include "Entities/Ball.h"

class BallBatchRenderer {
public:
    BallBatchRenderer(int segments = 12);

    void begin();
    void submit(const Ball& ball);
    void end();
    void draw(sf::RenderWindow& window) const;

private:
    int segments;
    sf::VertexArray vertexArray;
};
