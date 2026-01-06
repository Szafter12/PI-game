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

    std::vector<Weapon> arsenal;
    int weapon_index = 0;
    std::shared_ptr<sf::Texture> guns_texture;

    public:

    sf::Texture walkTxt = sf::Texture("../../assets/images/walk.png");
    sf::Texture idleTxt = sf::Texture("../../assets/images/Idle.png");
    sf::Sprite sprite = sf::Sprite(idleTxt);
    sf::Vector2f position {};
    sf::RectangleShape hpBar {};
    sf::RectangleShape plate {};
    int ad {};
    int armor {};
    int lvl {};
    float speed {};
    int nextLvlCap {};
    int currentXp {};
    WeaponType weapon {WeaponType::Gun1};
    //stats
    int maxHp=100;
    int hp=maxHp;

    Animation
        mDown = Animation(&sprite,8,0,0,48,64,0.1),
        mLeft = Animation(&sprite,8,0,64,48,64,0.1),
        mUp = Animation(&sprite,8,0,192,48,64,0.1),
        mRight = Animation(&sprite,8,0,320,48,64,0.1),
        IdleDown = Animation(&sprite,8,0,0,48,64,0.1),
        IdleLeft = Animation(&sprite,8,0,64,48,64,0.1),
        IdleUp = Animation(&sprite,8,0,192,48,64,0.1),
        IdleRight = Animation(&sprite,8,0,320,48,64,0.1);

    Player(sf::Vector2f position);

    void update(const sf::RenderWindow &window, const float dt);
    void draw(sf::RenderWindow &window) const;

    sf::FloatRect getBounds() const;
    void initHitBoxOutline();

    Weapon& get_current_weapon();
    void switch_weapon(int index);
    void lvlUp();
    bool isLvlUp() const;
    void drawHpBar(const sf::View &view);
    void pauseAnim(int a);
};

#endif //GAME_PI_PLAYER_H