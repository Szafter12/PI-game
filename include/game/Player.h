#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H
#include <iostream>


class Player {
    public:
    sf::Texture texture[8] = {sf::Texture("../../assets/images/HeroBase.png")};
    sf::Sprite sprite = sf::Sprite(texture[0]);
    sf::Vector2f position;

    Player(const char* texturePath,sf::Vector2f position) {
        if (!texture[0].loadFromFile(texturePath)) std::cout<<"Error loading texture"<<std::endl;
        this->position = position;
        sprite.setTexture(texture[0]);
        sprite.setPosition(position);
    }
    Player(sf::Vector2f position) {
        texture[0].loadFromFile("../../assets/images/HeroIdleUp.png");
        texture[1].loadFromFile("../../assets/images/HeroIdleUpR.png");
        texture[2].loadFromFile("../../assets/images/HeroIdleR.png");
        texture[3].loadFromFile("../../assets/images/HeroIdleDownR.png");
        texture[4].loadFromFile("../../assets/images/HeroBase.png");
        texture[5].loadFromFile("../../assets/images/HeroIdleDownL.png");
        texture[6].loadFromFile("../../assets/images/HeroIdleL.png");
        texture[7].loadFromFile("../../assets/images/HeroIdleUpL.png");
        this->position = position;
        sprite.setTexture(texture[0]);
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