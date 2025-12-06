#pragma once

#include <SFML/Graphics.hpp>

#ifndef GAME_PI_ENEMY_H
#define GAME_PI_ENEMY_H

enum class EnemyType {
    Basic
};

class Enemy {
    private:
        EnemyType type;
        float speed;
        sf::Sprite sprite;
        sf::Vector2f position;
    public:
        // Constructor/Destructor
        Enemy();
        ~Enemy();

        // Functions
        void update();
        void render(sf::RenderTarget* target);
};


#endif //GAME_PI_ENEMY_H