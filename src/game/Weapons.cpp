#include "../../include/game/Weapons.h"

Weapons::Weapons(WeaponType type_) : type(type_) {
    switch (this->type) {
        case WeaponType::BasicGun:
            this->ad = 40;
            break;
    }
}

WeaponType Weapons::get_weapon_type() const {
    return this->type;
}
