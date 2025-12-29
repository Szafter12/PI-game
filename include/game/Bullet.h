//
// Created by Mateusz Nosal on 21/12/2025.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>


#ifndef GAME_PI_BULLET_H
#define GAME_PI_BULLET_H


class Bullet {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float life_time;
    float max_life_time;
public:
    // Start position
    Bullet(sf::Vector2f start_position, sf::Vector2f target_position);
    void update(float dt);
    void render(sf::RenderTarget& target);

    sf::FloatRect getGlobalBounds() const;
    bool isDead() const;
};


#endif //GAME_PI_BULLET_H