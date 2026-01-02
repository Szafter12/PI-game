#include "../../include/states/UpgradeState.h"
#include <iostream>

UpgradeState::UpgradeState(sf::Font *font_)
    : font(font_), levelUpText(*this->font), secondText(*this->font), border1(this->borderTexture), border2(this->borderTexture), border3(this->borderTexture) {
    this->border1.setTextureRect(sf::IntRect({256,0}, {64, 64}));
    this->border2.setTextureRect(sf::IntRect({256,0}, {64, 64}));
    this->border3.setTextureRect(sf::IntRect({256,0}, {64, 64}));

    this->border1.setScale(sf::Vector2f(2.f,2.f));
    this->border2.setScale(sf::Vector2f(2.f,2.f));
    this->border3.setScale(sf::Vector2f(2.f,2.f));

    this->border1.setOrigin(sf::Vector2f(this->border1.getLocalBounds().size.x/2.f, this->border1.getLocalBounds().size.y/2.f));
    this->border2.setOrigin(sf::Vector2f(this->border2.getLocalBounds().size.x/2.f, this->border2.getLocalBounds().size.y/2.f));
    this->border3.setOrigin(sf::Vector2f(this->border3.getLocalBounds().size.x/2.f, this->border3.getLocalBounds().size.y/2.f));
}

void UpgradeState::draw(sf::RenderWindow &target) {
    target.draw(this->border1);
    target.draw(this->border2);
    target.draw(this->border3);
    this->levelUpText.setFillColor(sf::Color::Black);
    this->levelUpText.setCharacterSize(32);
    this->levelUpText.setString("Level Up");
    this->levelUpText.setOrigin(sf::Vector2f(this->levelUpText.getGlobalBounds().size.x/2.f, this->levelUpText.getGlobalBounds().size.y/2.f));
    target.draw(this->levelUpText);

    this->secondText.setFillColor(sf::Color::Black);
    this->secondText.setCharacterSize(18);
    this->secondText.setString("Wybierz ulepszenie");
    this->secondText.setOrigin(sf::Vector2f(this->secondText.getGlobalBounds().size.x/2.f, this->secondText.getGlobalBounds().size.y/2.f));
    target.draw(this->secondText);
}

void UpgradeState::setPosition(sf::Vector2f position) {
    this->border1.setPosition(sf::Vector2f(position.x - 130.f,position.y));
    this->border2.setPosition(sf::Vector2f(position.x,position.y));
    this->border3.setPosition(sf::Vector2f(position.x + 130.f,position.y));
    this->levelUpText.setPosition(sf::Vector2f(position.x,position.y - 120.f));
    this->secondText.setPosition(sf::Vector2f(position.x,position.y - 90.f));
}
