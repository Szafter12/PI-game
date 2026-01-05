#ifndef GAME_PI_UPGRADESTATE_H
#define GAME_PI_UPGRADESTATE_H

#include <SFML/Graphics.hpp>


class UpgradeState {
    private:
        sf::Texture borderTexture = {sf::Texture("assets/images/border.png")};
        sf::Font *font;
        sf::Text levelUpText;
        sf::Text secondText;
        sf::Sprite border1;
        sf::Sprite border2;
        sf::Sprite border3;

        std::vector<sf::Sprite> borders;
        void selectUpgrade();
        void setText();
        void setBorders();
    public:
        UpgradeState(sf::Font *font_);
        void draw(sf::RenderWindow &target);
        void update(float dt, sf::Vector2f position);
        void setPosition(sf::Vector2f position);
};


#endif //GAME_PI_UPGRADESTATE_H