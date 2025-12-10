#include "../../include/game/Enemy.h"

Enemy::Enemy(EnemyType type, sf::Vector2f position_, std::shared_ptr<sf::Texture> texture_)
    : position(position_), rotation(0.f), texture(std::move(texture_)), sprite(*texture) {
    switch (type) {
        case EnemyType::Basic:
            maxHp = 100;
            hp = maxHp;
            speed = 15.0f;
            rotation = 0.f;
            break;
    }
    sprite.setOrigin(sf::Vector2f(50.f,50.f));
    sprite.setPosition(position);
    sprite.setTextureRect(sf::IntRect({0, 0}, {100, 100}));
    sprite.scale(sf::Vector2f(scale, scale));
    sprite.setRotation(sf::degrees(this->rotation));
}

void Enemy::update(float dt, sf::Vector2f playerPosition) {
    updateAnimation(dt);
    updatePosition(dt, playerPosition);
}

void Enemy::render(sf::RenderTarget* target) {
    target->draw(sprite);
}

void Enemy::updatePosition(float dt, sf::Vector2f playerPosition) {
    // Calculating vector from Enemy to Player
    sf::Vector2f playerVectorDirection = playerPosition - this->position;

    // Vector normalization
    float length = playerVectorDirection.length();
    if (length != 0.f) playerVectorDirection /= length;

    // Enemy roation to Player
    float radians = std::atan2(playerVectorDirection.y, playerVectorDirection.x);
    float degrees = radians * 180.f / PI;

    // Calculating sprite velocity and position
    sf::Vector2f velocity;
    velocity.x = playerVectorDirection.x * this->speed;
    velocity.y = playerVectorDirection.y * this->speed;
    this->position.x += velocity.x * dt;
    this->position.y += velocity.y * dt;

    // if sprite change angle more than 90 degress
    if (degrees > 90) this->sprite.setScale(sf::Vector2f(scale, -scale));

    // Setting new position and rotate sprite
    this->rotation = degrees;
    this->sprite.setRotation(sf::degrees(this->rotation));
    this->sprite.setPosition(this->position);
}

void Enemy::updateAnimation(float dt) {
    frameTime += dt;
    if(frameTime >= frameDuration) {
        frameTime = 0.f;
        frame++;

        int maxFrames = 8;
        if(frame >= maxFrames) frame = 0;
        sprite.setTextureRect(sf::IntRect({frame * 100, 0}, {100,100}));
    }
}