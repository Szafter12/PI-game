#ifndef GAME_PI_UPGRADEUTILS_H
#define GAME_PI_UPGRADEUTILS_H

inline std::string upgradeToString(const Upgrade& u) {
    switch (u.type) {
        case UpgradeType::Speed:
            return "Predkosc + " + std::to_string(static_cast<int>(u.value));
        case UpgradeType::MaxHp:
            return "Max HP + " + std::to_string(static_cast<int>(u.value));
        case UpgradeType::Heal:
            return "Ulecz do max HP";
    }
    return "";
}

#endif //GAME_PI_UPGRADEUTILS_H