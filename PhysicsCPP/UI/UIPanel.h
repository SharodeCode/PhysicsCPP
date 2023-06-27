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
    UIPanel(float padding = 10.0f) : padding(padding), activeElement(nullptr) {}

    void addElement(const std::shared_ptr<UIElement>& element) {
        if (!elements.empty()) {
            auto& lastElement = elements.back();
            sf::Vector2f pos = lastElement->getPosition();
            pos.y += lastElement->getSize().y + padding;
            element->setPosition(pos);
        }
        elements.push_back(element);
    }

    void draw(sf::RenderWindow& window) override {
        for (auto& element : elements) {
            element->draw(window);
        }
    }

    void update(sf::Vector2i mousePosition) {
        // update child elements
        for (auto& element : elements) {
            element->update(mousePosition);
        }
    }

    bool handleEvent(const sf::Event& event, sf::Vector2i mousePosition) override {
        for (auto& element : elements) {
            if (element->handleEvent(event, mousePosition)) {
                return true;
            }
        }
        return false;
    }

    void setActiveElement(UIElement& element) {
        activeElement = &element;
    }

    UIElement* getActiveElement() {
        return activeElement;
    }

    //TODO: Modify this so that it doesnt implement the functions?
    sf::Vector2f getPosition() const override { return sf::Vector2f(4.f, 3.f); }
    void setPosition(const sf::Vector2f& position) override { /*...*/ }

    sf::Vector2f getSize() const override { return sf::Vector2f(4.f, 3.f); }
    void setSize(const sf::Vector2f& size) override { /*...*/ }

private:
    UIElement* activeElement;
};

