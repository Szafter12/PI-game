#ifndef GAME_PI_BULLET_H
#define GAME_PI_BULLET_H

#include <SFML/Graphics.hpp>
#include <cmath>

class Bullet {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float life_time;
    float max_life_time;
public:
    // Start position
    Bullet(sf::Vector2f start_position, sf::Vector2f target_position, const sf::Texture& texture);
    void update(float dt);
    void render(sf::RenderTarget& target);

    sf::FloatRect getGlobalBounds() const;
    bool isDead() const;
};


#endif //GAME_PI_BULLET_H