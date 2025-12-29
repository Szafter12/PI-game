//
// Created by Mateusz Nosal on 21/12/2025.
//

#include "../../include/game/Bullet.h"


Bullet::Bullet(sf::Vector2f start_position, sf::Vector2f target_position){
    this->shape.setRadius(5.f);
    this->shape.setFillColor(sf::Color::White);

    this->shape.setOrigin({5.f, 5.f});
    this->shape.setPosition(start_position);

    this->life_time = 0.f;
    this->max_life_time = 3.f;
    float speed = 500.f;

    sf::Vector2f direction = target_position - start_position;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
    }

    this->velocity = direction * speed;
}

void Bullet::update(float dt) {
    this->shape.move(this->velocity * dt);
    this->life_time += dt;
}

void Bullet::render(sf::RenderTarget& target) {
    target.draw(this->shape);
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return this->shape.getGlobalBounds();
}

bool Bullet::isDead() const {
    return this->life_time >= this->max_life_time;
}