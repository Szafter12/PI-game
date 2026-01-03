#ifndef GAME_PI_PLAYER_H
#define GAME_PI_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapons.h"


#include "Animation.h"

class Player {
    private:
    sf::RectangleShape hitBox;

    std::vector<Weapon> arsenal;
    int weapon_index = 0;
    std::shared_ptr<sf::Texture> guns_texture;

    void getAttack();

    public:
    sf::Texture texture = sf::Texture("assets/images/Player.png");
    sf::Sprite sprite = sf::Sprite(texture);
    sf::Vector2f position {};
    int ad {};
    WeaponType weapon {WeaponType::Gun1};
    Animation mDown = Animation(&sprite,2,0,0,32,32,1),
    mDownL = Animation(&sprite,2,0,32,32,32,1),
    mLeft = Animation(&sprite,2,0,64,32,32,1),
    mUpL = Animation(&sprite,2,0,96,32,32,1),
    mUp = Animation(&sprite,2,0,128,32,32,1),
    mUpR = Animation(&sprite,2,0,160,32,32,1),
    mRight = Animation(&sprite,2,0,192,32,32,1),
    mDownR = Animation(&sprite,2,0,224,32,32,1);

    Player(sf::Vector2f position);

    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
    void initHitBoxOutline();

    Weapon& get_current_weapon();
    void switch_weapon(int index);
};

#endif //GAME_PI_PLAYER_H