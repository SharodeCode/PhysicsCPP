#pragma once
#include <SFML/Graphics.hpp>
#include "UI/UIElement.h"
#include "UI/UIPanel.h"
#include "UI/UITheme.h"

class Button : public UIElement
{

    enum class VisualState {
        Inactive,
        Hovered,
        Active
    };


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

    Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, UIPanel& panel);
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

	void setVisualState(VisualState state);

private:
    UIPanel* m_panelGroup;

    bool active = false;

};

