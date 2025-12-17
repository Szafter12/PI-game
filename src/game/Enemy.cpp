#include "../../include/game/Enemy.h"

Enemy::Enemy(EnemyType type, sf::Vector2f position_, std::shared_ptr<sf::Texture> texture_)
    : texture(std::move(texture_)), sprite(*texture), position(position_) {
    // Switch between enemies types
    switch (type) {
        case EnemyType::Basic:
            this->maxHp = 100;
            this->hp = this->maxHp;
            this->speed = 50.0f;
            break;
    }

    // Set sprite basic settings
    this->sprite.setPosition(this->position);
    this->sprite.setTextureRect(sf::IntRect({0,0},{192/4,192/4}));
    this->scale = 2.f;
}

void Enemy::update(float dt, sf::Vector2f playerPosition) {
    updatePosition(dt, playerPosition);
    updateAnimation(dt);
    this->initHitBoxOutline();
}

void Enemy::render(sf::RenderTarget* target) const {
    target->draw(this->sprite);

    // Draw hitBox
    target->draw(this->hitBox);
}

void Enemy::updatePosition(float dt, sf::Vector2f playerPosition) {
    /*
        @return void
        - update enemy position based on where player is
    */

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
    if (degrees >= -45 && degrees < 45)
        direction = EnemyDirection::Right;
    else if (degrees >= 45 && degrees < 135)
        direction = EnemyDirection::Down;
    else if (degrees < -45 && degrees >= -135)
        direction = EnemyDirection::Up;
    else
        direction = EnemyDirection::Left;

    // Setting new position
    this->sprite.setPosition(this->position);
    sf::FloatRect bounds = this->sprite.getLocalBounds();
    this->sprite.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
    this->sprite.setScale(sf::Vector2f(this->scale, this->scale));
}

void Enemy::updateAnimation(float dt) {
    /*
        @return void
        - update enemy frame on spritesheet to add animations
    */

    if (direction != lastDirection) {
        frame = 0;
        frameTime = 0.f;
        lastDirection = direction;
    }

    this->frameTime += dt;
    if(this->frameTime >= this->frameDuration) {
        this->frameTime = 0.f;
        this->frame++;

        if(this->frame >= this->maxFrames) this->frame = 0;

        const int row = static_cast<int>(this->direction);

        int frameWidth  = 192 / 4;
        int frameHeight = 192 / 4;

        sprite.setTextureRect(
            sf::IntRect({
                frame * frameWidth,
                row * frameHeight,
                },{
                frameWidth,
                frameHeight
                }
            )
        );
    }
}

sf::FloatRect Enemy::getBounds() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.size.x = bounds.size.x / 3;
    bounds.size.y = bounds.size.y / 3;
    bounds.position.x = bounds.position.x + bounds.size.x;
    bounds.position.y = bounds.position.y + bounds.size.y;
    return bounds;
}

void Enemy::initHitBoxOutline() {
    sf::FloatRect bounds = this->getBounds();

    this->hitBox.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
    this->hitBox.setSize(sf::Vector2f(bounds.size.x, bounds.size.y));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Red);
    this->hitBox.setOutlineThickness(1.f);
}
