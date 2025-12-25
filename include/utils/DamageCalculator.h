#ifndef GAME_PI_DAMAGECALCULATOR_H
#define GAME_PI_DAMAGECALCULATOR_H

#include "../game/Weapons.h"

class DamageCalculator {
    public:
        static int calculateFlatDamage(int ad, Weapons weapon);
};


#endif //GAME_PI_DAMAGECALCULATOR_H