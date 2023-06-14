#pragma once
#include <SFML/Graphics.hpp>

class Button
{
    sf::RectangleShape button;
    sf::Text text;

public:
    Button(float x, float y, float width, float height, std::string buttonText, sf::Font& font);
    void drawTo(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};

