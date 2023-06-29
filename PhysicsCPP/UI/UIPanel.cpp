#include "UIPanel.h"

UIPanel::UIPanel(float padding) : padding(padding), activeElement(nullptr)
{

}

void UIPanel::addElement(const std::shared_ptr<UIElement>& element)
{
    if (!elements.empty()) {
        auto& lastElement = elements.back();
        sf::Vector2f pos = lastElement->getPosition();
        pos.y += lastElement->getSize().y + padding;
        element->setPosition(pos);
    }
    elements.push_back(element);
}

void UIPanel::draw(sf::RenderWindow& window) {
    for (auto& element : elements) {
        element->draw(window);
    }
}

void UIPanel::update(sf::Vector2i mousePosition) {
    // update child elements
    for (auto& element : elements) {
        element->update(mousePosition);
    }
}

bool UIPanel::handleEvent(const sf::Event& event, sf::Vector2i mousePosition) {
    for (auto& element : elements) {
        if (element->handleEvent(event, mousePosition)) {
            return true;
        }
    }
    return false;
}

void UIPanel::setActiveElement(UIElement& element) {
    activeElement = &element;
}

UIElement* UIPanel::getActiveElement() {
    return activeElement;
}

//TODO: Modify this so that it doesnt implement the functions?
sf::Vector2f UIPanel::getPosition() const { return sf::Vector2f(4.f, 3.f); }
void UIPanel::setPosition(const sf::Vector2f& position) { /*...*/ }

sf::Vector2f UIPanel::getSize() const { return sf::Vector2f(4.f, 3.f); }
void UIPanel::setSize(const sf::Vector2f& size) { /*...*/ }