#pragma once

#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
    private:
    sf::RectangleShape hitBox;

    public:
    sf::Texture texture[8] = {sf::Texture("../../assets/images/HeroBase.png")};
    sf::Sprite sprite = sf::Sprite(texture[0]);
    sf::Vector2f position {};

    Player(sf::Vector2f position);

    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
    void initHitBoxOutline();
};

#endif //GAME_PI_PLAYER_H