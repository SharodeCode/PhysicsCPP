#pragma once
#include <SFML/Graphics.hpp>

struct UITheme {
    static inline sf::Font font;
    static inline sf::Color colourInactive = sf::Color::Blue;
    static inline sf::Color colourHover = sf::Color::Cyan;
    static inline sf::Color colourActive = sf::Color::Green;

    bool loadFont(const std::string& path) {
        return font.loadFromFile(path);
    }

    static sf::Font& getFont() {
        static sf::Font font;
        static bool loaded = font.loadFromFile("./Media/Fonts/Roboto.ttf");
        return font;
    }
};