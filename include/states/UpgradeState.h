#ifndef GAME_PI_UPGRADESTATE_H
#define GAME_PI_UPGRADESTATE_H

#include <SFML/Graphics.hpp>
#include "../game/Upgrade.h"
#include <cstdlib>

enum class UpgradeChoice {
    None,
    First,
    Second,
    Third
};

class UpgradeState {
    private:
        sf::Texture borderTexture = {sf::Texture("../../assets/images/border.png")};
        sf::Font *font;
        sf::Text levelUpText;
        sf::Text secondText;
        sf::Sprite border1;
        sf::Sprite border2;
        sf::Sprite border3;

        sf::Text upgradeText1;
        sf::Text upgradeText2;
        sf::Text upgradeText3;

        // 🔹 PRZYCISKI
        sf::RectangleShape button1;
        sf::RectangleShape button2;
        sf::RectangleShape button3;

        sf::Text buttonText1;
        sf::Text buttonText2;
        sf::Text buttonText3;

        UpgradeChoice selected = UpgradeChoice::None;

        std::vector<sf::Sprite> borders;
        std::array<Upgrade, 3> upgrades;

        void setButtons();
        void setText();
        void setBorders();
    public:
        UpgradeState(sf::Font *font_);
        void updateTexts();
        void rollUpgrades();
        Upgrade getUpgrade(UpgradeChoice choice) const;
        void draw(sf::RenderWindow &target) const;
        void update(float dt, sf::Vector2f position);
        void setPosition(sf::Vector2f position);
        void handleClick(sf::Vector2f mousePos);
        UpgradeChoice getSelected() const;
        void resetSelection();
};


#endif //GAME_PI_UPGRADESTATE_H