#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement.h"
#include <UI/UIPanel.h>

class Button : public UIElement
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

    Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, sf::Font& font, UIPanel& panel);
    bool isMouseOver(sf::Vector2i mousePosition);
    void update(sf::Vector2i mousePosition);

    void setPanelgroup(UIPanel& UIPanel);

    void draw(sf::RenderWindow& window) override;
    bool handleEvent(const sf::Event& event, sf::Vector2i mousePosition) override;

    sf::Vector2f getPosition() const override { return button.getPosition(); }
    void setPosition(const sf::Vector2f& position) override { button.setPosition(position); }

    sf::Vector2f getSize() const override { return button.getSize(); }
    void setSize(const sf::Vector2f& size) override { button.setSize(size); }

    void toggleActive();

private:
    sf::Color colourActive = sf::Color::Red;
    sf::Color colourInactive = sf::Color::Blue;
    sf::Color colourHover = sf::Color::Green;

    UIPanel* m_panelGroup;

    bool active = false;

};

