#ifndef GAME_PI_UPGRADE_H
#define GAME_PI_UPGRADE_H

enum class UpgradeType {
    Speed,
    MaxHp,
    Heal,
};

struct Upgrade {
    UpgradeType type;
    float value;
};

#endif //GAME_PI_UPGRADE_H