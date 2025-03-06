#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class UIElement {
public:
    //TODO: Modify so that the render window is not being passed around so much
    virtual void draw(sf::RenderWindow& window) = 0; // Pure virtual function for drawing
    virtual void update(sf::Vector2i mousePosition) = 0; // Pure virtual function for updating
    virtual bool handleEvent(const sf::Event& event, sf::Vector2i mousePosition) = 0; // Pure virtual function for handling events

    // Getters and setters for position.
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f& position) = 0;

    // Getters and setters for size.
    virtual sf::Vector2f getSize() const = 0;
    virtual void setSize(const sf::Vector2f& size) = 0;
};