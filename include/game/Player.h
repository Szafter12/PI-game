#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H
#include <iostream>

#include "Animation.h"


class Player {
    public:
    sf::Texture texture = {sf::Texture("../../assets/images/Player.png")};
    sf::Sprite sprite = sf::Sprite(texture);
    sf::Vector2f position;

    Player(const char* texturePath,sf::Vector2f position) {
        if (!texture.loadFromFile(texturePath)) std::cout<<"Error loading texture"<<std::endl;
        this->position = position;
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }
    Player(sf::Vector2f position) {
        //texture.loadFromFile("../../assets/images/Player.png");
        this->position = position;
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }

    void update(sf::RenderWindow &window) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            sprite.move({-1,0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            sprite.move({1,0});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
            sprite.move({0,-1});
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            sprite.move({0,1});
        }

        position = sprite.getPosition();
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (mousePos.y > position.y &&
            mousePos.y < (position.y+sprite.getTexture().getSize().y)) {
            if (mousePos.x < position.x) sprite.setTexture(texture[6]);
            else sprite.setTexture(texture[2]);
        }
        else if (mousePos.y < position.y) {
            if (mousePos.x < position.x) sprite.setTexture(texture[7]);
            else if (mousePos.x > position.x &&
                mousePos.x < (position.x+sprite.getTexture().getSize().x)) sprite.setTexture(texture[0]);
            else sprite.setTexture(texture[1]);
        }
        else {
            if (mousePos.x < position.x) sprite.setTexture(texture[5]);
            else if (mousePos.x > position.x &&
                mousePos.x < (position.x+sprite.getTexture().getSize().x)) sprite.setTexture(texture[4]);
            else sprite.setTexture(texture[3]);
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }
};

#endif //GAME_PI_PLAYER_H