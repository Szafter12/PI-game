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

enum class EnemyDirection {
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3,
};

class Enemy {
    private:
        // Private properties
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        sf::Vector2f position {};
        float scale {2.f};
        EnemyDirection direction = EnemyDirection::Down;
        EnemyDirection lastDirection = direction;
        sf::RectangleShape hitBox;

        float speed {};
        int maxHp {};
        int hp {};

        EnemyState state = EnemyState::Run;
        int frame {0};
        int maxFrames {4};
        float frameTime {0.f};
        float frameDuration = {0.1f};

        // Private methods
        void updateAnimation(float dt);
        void updatePosition(float dt, sf::Vector2f playerPosition);

    public:
        // Constructor/Destructor
        Enemy(EnemyType type, sf::Vector2f position_, std::shared_ptr<sf::Texture> texture_);

        // Core Methods
        void update(float dt, sf::Vector2f playerPosition);
        void render(sf::RenderTarget* target);

        // Other Methods
        sf::FloatRect getBounds() const;
        void initHitBox();
};


#endif //GAME_PI_ENEMY_H