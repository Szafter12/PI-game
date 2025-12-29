#ifndef GAME_PI_WEAPONS_H
#define GAME_PI_WEAPONS_H

enum class WeaponType {
    BasicGun
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