#pragma once
#include <SFML/Graphics.hpp>

class Button
{

public:
    enum buttonType
    {
        mute,
        ballSpawner,
        clickToSpawn
    };

    sf::RectangleShape button;
    sf::Text text;
    buttonType m_btnType;

    Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, sf::Font& font);
    void drawTo(sf::RenderWindow& window);
    bool isMouseOver(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);

    void toggleActive();

private:
    sf::Color colourActive = sf::Color::Red;
    sf::Color colourInactive = sf::Color::Blue;
    sf::Color colourHover = sf::Color::Green;

    bool active = false;

};

