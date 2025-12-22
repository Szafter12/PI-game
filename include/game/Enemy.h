#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include <iostream>

#ifndef GAME_PI_ENEMY_H
#define GAME_PI_ENEMY_H

inline constexpr double PI = 3.14159265359;

enum class EnemyType {
    Basic
};

enum class EnemyState {
    Idle,
    Run,
    Attack
};

class Enemy {
    private:
        // Private properties
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        float rotation;
        float scale = 2.f;

        float speed;
        int maxHp;
        int hp;

        EnemyState state = EnemyState::Idle;
        int frame = 0;
        float frameTime = 0.f;
        float frameDuration = 0.1f;

        // Private methods
        void updateAnimation(float dt);
        void updatePosition(float dt, sf::Vector2f playerPosition);

    public:
        // Constructor/Destructor
        Enemy(EnemyType type, sf::Vector2f position_, std::shared_ptr<sf::Texture> texture_);

        // Core Methods
        void update(float dt, sf::Vector2f playerPosition);
        void render(sf::RenderTarget* target);

        //Enemy hitbox
        auto getGlobalBounds() const {
            float width = 50.f;
            float height = 50.f;

            return sf::FloatRect({this->position.x - (width / 2.f), this->position.y - (height / 2.f)}, {width, height});
        }

        sf::Vector2f getPosition() const {
            return this->position;
        }
};


#endif //GAME_PI_ENEMY_H