#include "../../include/utils/DamageCalculator.h"

int DamageCalculator::calculateFlatDamage(int ad, Weapons weapon) {
    return ad + weapon.ad;
}
