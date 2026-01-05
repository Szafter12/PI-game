#include "../../include/utils/DamageCalculator.h"

int DamageCalculator::calculateFlatDamage(int ad, int armor) {
    return ad - armor;
}
