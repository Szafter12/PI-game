#include "../../include/game/Enemy.h"
#include "../../include/game/Player.h"
#include "../../include/utils/Collider.h"
#include "../../include/utils/DamageCalculator.h"
#include "../../include/game/Weapons.h"

#include <memory>
#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

Enemy::Enemy(EnemyType type, sf::Vector2f position_)
    : position(position_), sprite(this->textureRun) {
    // Switch between enemies types
    switch (type) {
        case EnemyType::Basic:
            this->maxHp = 100;
            this->hp = this->maxHp;
            this->speed = 50.0f;
            this->ad = 20;
            this->armor = 10;
            break;
    }

    // Set sprite basic settings
    this->sprite.setPosition(this->position);
    this->sprite.setTextureRect(sf::IntRect({0,0},{192/4,192/4}));
    this->scale = {2.f};
}

void Enemy::update(float dt, sf::Vector2f playerPosition) {
    if (!this->isAttacking) {
        updatePosition(dt, playerPosition);
    }
    // this->initHitBoxOutline();
    this->updateAnimation(dt);
}

void Enemy::render(sf::RenderTarget* target) const {
    target->draw(this->sprite);

    // Draw hitBox
    // target->draw(this->hitBox);
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
    this->velocity.x = playerVectorDirection.x * this->speed;
    this->velocity.y = playerVectorDirection.y * this->speed;
    this->position.x += velocity.x * dt;
    this->position.y += velocity.y * dt;

    // if sprite change angle more than 90 degress
    if (degrees >= -45 && degrees <= 45)
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

    if (!this->isAttacking && this->direction != this->lastDirection) {
        this->resetAnimation();
        this->lastDirection = this->direction;
    }

    this->frameTime += dt;
    float currentFrameDuration = (state == EnemyState::Run) ? frameDuration : frameDurationAttack;

    if (frameTime >= currentFrameDuration) {
        this->frameTime = 0.f;
        this->frame++;

        int maxFrame {};
        int frameWidth {};
        int frameHeight {};

        if (this->state == EnemyState::Run) {
            maxFrame = 4;
            frameWidth  = 192 / maxFrame;
            frameHeight = 192 / 4;
        } else if (this->state == EnemyState::Attack) {
            maxFrame = 2;
            frameWidth  = 96 / maxFrame;
            frameHeight = 576 / 12;
        }

        if (state == EnemyState::Attack && this->frame >= maxFrame) {
            isAttacking = false;
            this->setState(EnemyState::Run);
            this->resetAnimation();
        }

        if(this->frame >= maxFrame) this->frame = 0;

        const int row = static_cast<int>(this->direction);
        sprite.setTextureRect(
            sf::IntRect({
                this->frame * frameWidth,
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

sf::Vector2f Enemy::getPosition() const {
    return this->position;
}

void Enemy::checkCollisionWithOtherEnemies(Enemy &other, float dt) {
    const sf::FloatRect a = this->getBounds();
    const sf::FloatRect b = other.getBounds();

    if (!a.findIntersection(b)) return;

    Collider::calculatePosition(*this, other, dt);
}

void Enemy::collideWithPlayer (Player &player, float dt) {
    sf::FloatRect playerBounds = player.getBounds();

    if (!playerBounds.findIntersection(this->getBounds())) {
        if (isAttacking) return;
        this->setState(EnemyState::Run);
        return;
    }

    if (this->state != EnemyState::Attack) {
        this->startAttack();
    }

    Collider::calculatePosition(player, *this, dt);
}

bool Enemy::is_alive() const {
    return this->hp > 0;
}

void Enemy::getAttack(int ad, Weapons weapon) {
    this->hp -= DamageCalculator::calculateFlatDamage(ad, weapon);
}

void Enemy::startAttack() {
    if (isAttacking) return;

    isAttacking = true;
    this->setState(EnemyState::Attack);
    this->resetAnimation();
}

void Enemy::enemyChangeTexture() {
    this->resetAnimation();

    switch (state) {
        case EnemyState::Run:
            sprite.setTexture(textureRun, true);
            sprite.setTextureRect(sf::IntRect({0,0},{192/4,192/4}));
            break;

        case EnemyState::Attack:
            sprite.setTexture(textureAttack, true);
            sprite.setTextureRect(sf::IntRect({0,0},{96/2,576/12}));
            break;
        default:
            sprite.setTexture(textureRun, true);
            sprite.setTextureRect(sf::IntRect({0,0},{192/4,192/4}));
            break;
    }
}

void Enemy::resetAnimation() {
    this->frame = 0;
    this->frameTime = 0.f;
}

void Enemy::setState(EnemyState newState) {
    if (state == newState) return;

    state = newState;
    enemyChangeTexture();
}


