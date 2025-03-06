#include "UI/Button.h"

Button::Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, sf::Font& font, UIPanel& panel) {
    m_btnType = btnType;
    m_panelGroup = &panel;
    
    button.setPosition(sf::Vector2f(x, y));
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(colourInactive);

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(button.getPosition());
}

bool Button::isMouseOver(sf::Vector2i mousePosition) {
    float mouseX = mousePosition.x;
    float mouseY = mousePosition.y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;
    float btnxPosWidth = btnPosX + button.getLocalBounds().width;
    float btnyPosHeight = btnPosY + button.getLocalBounds().height;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

void Button::setPanelgroup(UIPanel& UIPanel) {
    m_panelGroup = &UIPanel;
}

bool Button::handleEvent(const sf::Event& event, sf::Vector2i mousePosition) {

    if (event.type == sf::Event::MouseButtonPressed && isMouseOver(mousePosition)) {
        toggleActive();
        if (active) {
            m_panelGroup->setActiveElement(*this); // Assumes "ui" is a reference to the UI, you'll need to pass it to Button in some way
        }
        else {
            //m_panelGroup->setActiveElement(nullptr);
        }
        return true; // event is consumed
    }
    return false;
}

void Button::update(sf::Vector2i mousePosition) {
    // update button color based on mouse over
    if (isMouseOver(mousePosition)) {
        button.setFillColor(colourHover);
    }
    else if (active) {
        button.setFillColor(colourActive);
    }
    else {
        button.setFillColor(colourInactive);
    }
}

void Button::toggleActive() {

    active = !active;

}
