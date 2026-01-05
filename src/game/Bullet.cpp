//
// Created by Mateusz Nosal on 21/12/2025.
//

#include "../../include/game/Bullet.h"


Bullet::Bullet(sf::Vector2f start_position, sf::Vector2f target_position, const sf::Texture& texture) : sprite(texture) {
    // this->shape.setRadius(5.f);
    // this->shape.setFillColor(sf::Color::White);
    //
    // this->shape.setOrigin({5.f, 5.f});
    // this->shape.setPosition(start_position);

    this->sprite.setTexture(texture);
    sf::Vector2u size = texture.getSize();
    this->sprite.setOrigin({static_cast<float>(size.x / 2.f), static_cast<float>(size.y / 2.f)});
    this->sprite.setPosition(start_position);
    this->sprite.setScale({0.5, 0.5});



    this->life_time = 0.f;
    this->max_life_time = 3.0f;
    float speed = 200.f;

    sf::Vector2f direction = target_position - start_position;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length != 0) {
        direction /= length;
        float rotation = std::atan(direction.y / direction.x) * 180.f / 3.14159f;
        this->sprite.setRotation(sf::degrees(rotation));
    }

    this->velocity = direction * speed;
}

void Bullet::update(float dt) {
    this->sprite.move(this->velocity * dt);
    this->life_time += dt;
}

void Bullet::render(sf::RenderTarget& target) {
    target.draw(this->sprite);
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return this->sprite.getGlobalBounds();
}

bool Bullet::isDead() const {
    return this->life_time >= this->max_life_time;
}