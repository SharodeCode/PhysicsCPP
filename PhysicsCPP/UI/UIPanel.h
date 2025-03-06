#pragma once
#include <vector>
#include <memory>
#include "UI/UIElement.h"

//TODO: Panel into .h and .cpp file
//TODO: Panel into vertical and horixontal layout
class UIPanel : public UIElement {
    std::vector<std::shared_ptr<UIElement>> elements;
    float padding;


public:
    UIPanel(float padding = 10.0f);

    void addElement(const std::shared_ptr<UIElement>& element);

    void draw(sf::RenderWindow& window) override;

    void update(sf::Vector2i mousePosition);

    bool handleEvent(const sf::Event& event, sf::Vector2i mousePosition) override;

    void setActiveElement(UIElement& element);

    UIElement* getActiveElement();

    //TODO: Modify this so that it doesnt implement the functions?
    sf::Vector2f getPosition() const override;
    void setPosition(const sf::Vector2f& position);

    sf::Vector2f getSize() const override;
    void setSize(const sf::Vector2f& size);

private:
    UIElement* activeElement;
};

