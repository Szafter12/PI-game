#include "../../include/utils/Collider.h"
#include "../../include/game/Player.h"
#include "../../include/game/Enemy.h"

#include <SFML/Graphics.hpp>
#include <cmath>

void Collider::calculatePosition(Enemy &enemy1, Enemy &enemy2, float dt) {
    sf::Vector2f delta = enemy2.position - enemy1.position;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (dist == 0.f) return;

    sf::Vector2f normal = delta / dist;

    float push = enemy1.speed * dt;
    enemy1.position -= normal * push;
    enemy2.position += normal * push;

    enemy1.sprite.setPosition(enemy1.position);
    enemy2.sprite.setPosition(enemy2.position);
}

void Collider::calculatePosition(Player &player, Enemy &enemy, float dt) {
    sf::Vector2f delta = player.position - enemy.position;
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (dist == 0.f) return;

    sf::Vector2f normal = delta / dist;

    float push = enemy.speed * dt;
    enemy.position -= normal * push;
    player.position += normal * push;

    enemy.sprite.setPosition(enemy.position);
    player.sprite.setPosition(player.position);
}