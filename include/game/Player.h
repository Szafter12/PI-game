#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Weapons.h"


#include "Animation.h"

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
    //stats
    int maxHp=100;
    int hp=maxHp;
    float speed=1;

    WeaponType weapon {WeaponType::BasicGun};
    Animation
        mDown = Animation(&sprite,8,0,0,48,64,0.1),
        mLeft = Animation(&sprite,8,0,64,48,64,0.1),
        mUp = Animation(&sprite,8,0,192,48,64,0.1),
        mRight = Animation(&sprite,8,0,320,48,64,0.1);

    Player(sf::Vector2f position);

    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
    void initHitBoxOutline();
    void drawHpBar();
};

#endif //GAME_PI_PLAYER_H