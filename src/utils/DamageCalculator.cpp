#include "../../include/utils/DamageCalculator.h"

int DamageCalculator::calculateFlatDamage(int ad, Weapons weapon, int armor) {
    return ad + weapon.ad - armor;
}
