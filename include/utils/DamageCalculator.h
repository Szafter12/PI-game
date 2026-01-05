#ifndef GAME_PI_DAMAGECALCULATOR_H
#define GAME_PI_DAMAGECALCULATOR_H

#include "../game/Weapons.h"

class DamageCalculator {
    public:
        static int calculateFlatDamage(int ad, int armor);
};


#endif //GAME_PI_DAMAGECALCULATOR_H