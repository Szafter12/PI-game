#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapons.h"


#include "Animation.h"
#include "Enemy.h"

class Player {
    private:
    sf::RectangleShape hitBox;

    void getAttack();

    public:
    sf::Texture texture = sf::Texture("../../assets/images/walk.png");
    sf::Sprite sprite = sf::Sprite(texture);
    sf::Vector2f position {};
    sf::RectangleShape hpBar {};
    int ad {};
    int armor {};
    int lvl {};
    float speed {};
    int nextLvlCap {};
    int currentXp {};
    //stats
    int maxHp=100;
    int hp=maxHp;

    WeaponType weapon {WeaponType::BasicGun};
    Animation
        mDown = Animation(&sprite,8,0,0,48,64,0.1),
        mLeft = Animation(&sprite,8,0,64,48,64,0.1),
        mUp = Animation(&sprite,8,0,192,48,64,0.1),
        mRight = Animation(&sprite,8,0,320,48,64,0.1);

    Player(sf::Vector2f position);

    void update(const sf::RenderWindow &window, const float dt);
    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
    void initHitBoxOutline();
    void lvlUp();
    bool isLvlUp();
    void drawHpBar();
};

#endif //GAME_PI_PLAYER_H