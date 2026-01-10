#include "../../include/game/Weapons.h"

Weapons::Weapons(WeaponType type_) : type(type_) {}

WeaponType Weapons::get_weapon_type() const {
    return this->type;
}
