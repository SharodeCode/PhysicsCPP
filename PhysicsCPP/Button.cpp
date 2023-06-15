#include "Button.h"

Button::Button(buttonType btnType, float x, float y, float width, float height, std::string buttonText, sf::Font& font) {
    m_btnType = btnType;
    
    button.setPosition(sf::Vector2f(x, y));
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(sf::Color::Blue);

    text.setFont(font);
    text.setString(buttonText);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(button.getPosition());
}

void Button::drawTo(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(text);
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    float mouseX = sf::Mouse::getPosition(window).x;
    float mouseY = sf::Mouse::getPosition(window).y;

    float btnPosX = button.getPosition().x;
    float btnPosY = button.getPosition().y;
    float btnxPosWidth = btnPosX + button.getLocalBounds().width;
    float btnyPosHeight = btnPosY + button.getLocalBounds().height;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

void Button::update(sf::RenderWindow& window) {
    if (isMouseOver(window)) {
        button.setFillColor(sf::Color::Red);
    }
    else {
        button.setFillColor(sf::Color::Blue);
    }
}
