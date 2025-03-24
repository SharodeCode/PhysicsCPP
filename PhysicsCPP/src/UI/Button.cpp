#include "UI/Button.h"

Button::Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, UIPanel& panel)
{
    m_btnType = btnType;
    m_panelGroup = &panel;
    
    button.setPosition(sf::Vector2f(x, y));
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(UITheme::colourInactive);

    text.setFont(UITheme::getFont());
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    text.setPosition(button.getPosition().x + button.getSize().x / 2.f,
    button.getPosition().y + button.getSize().y / 2.f);
}

bool Button::isMouseOver(sf::Vector2i mousePosition) {
    float mouseX = static_cast<float>(mousePosition.x);
    float mouseY = static_cast<float>(mousePosition.y);

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
            m_panelGroup->setActiveElement(*this);
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
        setVisualState(VisualState::Hovered);
    }
    else if (active) {
        setVisualState(VisualState::Active);
    }
    else {
        setVisualState(VisualState::Inactive);
    }
}

void Button::toggleActive(){

    active = !active;

}

void Button::setVisualState(VisualState state) {
    switch (state) {
    case VisualState::Hovered: button.setFillColor(UITheme::colourHover); break;
    case VisualState::Active:  button.setFillColor(UITheme::colourActive); break;
    case VisualState::Inactive: button.setFillColor(UITheme::colourInactive); break;
    }
}
