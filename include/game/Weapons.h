#ifndef GAME_PI_WEAPONS_H
#define GAME_PI_WEAPONS_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

enum class WeaponType {
    Gun1,
    Gun2,
    Gun3,
    Gun4,
    Gun5,
    Gun6,
    Gun7,
    Gun8,
    Grenade
};

struct Weapon {
    std::string name;
    float fire_rate;
    int damage;
    float bullet_speed;
    WeaponType type;

    std::shared_ptr<sf::Texture> texture;
    sf::Sprite icon;

    Weapon(const std::string &n, float rate, int dmg, float speed, WeaponType t,
        const std::shared_ptr<sf::Texture> &tex, sf::IntRect rect):
    name(n),
    fire_rate(rate),
    damage(dmg),
    bullet_speed(speed),
    type(t),
    texture(tex),
    icon(*tex) {
        this->icon.setTextureRect(rect);
        this->icon.setScale({1, 1});
    }

};

class Weapons {
    WeaponType type {};

    public:
        int ad {};
        bool isMele {};

        Weapons(WeaponType type_);
        WeaponType get_weapon_type() const;
};


#endif //GAME_PI_WEAPONS_H