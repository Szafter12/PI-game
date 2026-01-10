//
// Created by PanPytajnik on 06.01.2026.
//

#ifndef GAME_PI_BUTTON_H
#define GAME_PI_BUTTON_H
#include "SFML/Graphics/RectangleShape.hpp"
#include <iostream>

#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

class Button {
public:
    sf::RectangleShape rect;
    std::string label;
    sf::Font font = sf::Font("../../assets/fonts/Cristone.ttf");
    sf::Text text = sf::Text(font);
    sf::Vector2f size;
    sf::Vector2f position;
    bool isClicked=false;

    Button(std::string label,sf::Vector2f position, sf::Vector2f size) {
        this->label = label;
        this->size = size;
        this->position = position;
        text.setFillColor(sf::Color::Black);
        text.setString(label);
        text.setOrigin({text.getGlobalBounds().size.x/2,text.getGlobalBounds().size.y/2});
        text.setPosition({position.x, position.y-5});
        text.setScale({0.75,0.75});

        rect.setSize(size);
        rect.setOrigin({size.x/2,size.y/2});
        rect.setPosition(position);

        rect.setFillColor(sf::Color(128,128,128,255));
        rect.setOutlineColor(sf::Color::Black);
        rect.setOutlineThickness(2);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(rect);
        window.draw(text);
    }
    void update(sf::RenderWindow &window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (mousePos.x>rect.getPosition().x-size.x/2 && mousePos.x<rect.getPosition().x+rect.getSize().x/2 &&
            mousePos.y>rect.getPosition().y-size.y/2 && mousePos.y<rect.getPosition().y+rect.getSize().y/2) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                //rect.setFillColor(sf::Color::White);
                rect.setOutlineColor(sf::Color::White);
                isClicked=true;
            }
            else {
                //rect.setFillColor(sf::Color(128,128,128,255));
                rect.setOutlineColor(sf::Color::White);
                isClicked=false;
            }
        }
        else {
            rect.setFillColor(sf::Color(128,128,128,255));
            rect.setOutlineColor(sf::Color::Black);
            isClicked=false;
        }
        rect.setPosition(window.getView().getCenter()+position);
        text.setString(label);
        text.setPosition({rect.getPosition().x, rect.getPosition().y-5});
    }
};

#endif //GAME_PI_BUTTON_H