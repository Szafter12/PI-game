#include "../../include/states/UpgradeState.h"
#include "../../include/utils/UpgradeUtils.h"

UpgradeState::UpgradeState(sf::Font *font_)
    : font(font_), levelUpText(*font), secondText(*font),
      border1(borderTexture), border2(borderTexture), border3(borderTexture), upgradeText1(*font), upgradeText2(*font),
      upgradeText3(*font),
      buttonText1(*font),
      buttonText2(*font),
      buttonText3(*font) {
    setBorders();
    setText();
    setButtons();
    updateTexts();
}

void UpgradeState::setButtons() {
    auto setupButton = [&](sf::RectangleShape& btn, sf::Text& txt) {
        btn.setSize({30.f, 15.f});
        btn.setFillColor(sf::Color::Transparent);
        btn.setOrigin(btn.getSize() / 2.f);

        txt.setFont(*font);
        txt.setString("Wybierz");
        txt.setCharacterSize(18);
        sf::FloatRect bounds = txt.getGlobalBounds();
        txt.setOrigin(sf::Vector2f(bounds.size.x / 2.f, bounds.size.y / 2.f));
        txt.setScale(sf::Vector2f(0.7f, 0.7f));
        txt.setFillColor(sf::Color::White);
    };

    setupButton(button1, buttonText1);
    setupButton(button2, buttonText2);
    setupButton(button3, buttonText3);
}

void UpgradeState::draw(sf::RenderWindow &target) const {
    target.draw(this->border1);
    target.draw(this->border2);
    target.draw(this->border3);
    // target.draw(this->levelUpText);
    // target.draw(this->secondText);
    target.draw(button1);
    target.draw(button2);
    target.draw(button3);

    target.draw(buttonText1);
    target.draw(buttonText2);
    target.draw(buttonText3);

    target.draw(upgradeText1);
    target.draw(upgradeText2);
    target.draw(upgradeText3);
}

void UpgradeState::update(float dt, sf::Vector2f position) {
    this->setPosition(position);
}


void UpgradeState::updateTexts() {
        auto setupText = [](sf::Text& txt, const Upgrade& upg) {
            txt.setString(upgradeToString(upg));
            sf::FloatRect b = txt.getGlobalBounds();
            txt.setOrigin(sf::Vector2f(b.size.x / 2.f, b.size.y / 2.f));
            txt.setScale(sf::Vector2f(0.7f,0.7f));
        };

        setupText(upgradeText1, upgrades[0]);
        setupText(upgradeText2, upgrades[1]);
        setupText(upgradeText3, upgrades[2]);
}

Upgrade randomUpgrade() {
    int type = rand() % 3;

    switch (type) {
        case 0: return { UpgradeType::Speed, 10.f };
        case 1: return { UpgradeType::MaxHp, 25.f };
        case 2: return { UpgradeType::Heal, 0.f };
    }
    return { UpgradeType::Speed, 5.f };
}

void UpgradeState::rollUpgrades() {
    for (int i = 0; i < 3; ++i)
        upgrades[i] = randomUpgrade();

    updateTexts();
}

void UpgradeState::setPosition(sf::Vector2f position) {
    this->border1.setPosition(sf::Vector2f(position.x - 130.f,position.y));
    this->border2.setPosition(sf::Vector2f(position.x,position.y));
    this->border3.setPosition(sf::Vector2f(position.x + 130.f,position.y));
    this->levelUpText.setPosition(sf::Vector2f(position.x,position.y - 120.f));
    this->secondText.setPosition(sf::Vector2f(position.x,position.y - 90.f));
    button1.setPosition(sf::Vector2f(border1.getPosition().x, border1.getPosition().y + 40.f));
    button2.setPosition(sf::Vector2f(border2.getPosition().x, border2.getPosition().y + 40.f));
    button3.setPosition(sf::Vector2f(border3.getPosition().x, border3.getPosition().y + 40.f));

    buttonText1.setPosition(button1.getPosition());
    buttonText2.setPosition(button2.getPosition());
    buttonText3.setPosition(button3.getPosition());

    upgradeText1.setPosition(sf::Vector2f(border1.getPosition().x - 10.f, border1.getPosition().y - 10.f));
    upgradeText2.setPosition(sf::Vector2f(border2.getPosition().x - 10.f, border2.getPosition().y - 10.f));
    upgradeText3.setPosition(sf::Vector2f(border3.getPosition().x - 10.f, border3.getPosition().y - 10.f));
}

void UpgradeState::setText() {
    this->levelUpText.setFillColor(sf::Color::Black);
    this->levelUpText.setCharacterSize(48);
    this->levelUpText.setString("Level Up");
    this->levelUpText.setOrigin(sf::Vector2f(this->levelUpText.getGlobalBounds().size.x/2.f, this->levelUpText.getGlobalBounds().size.y/2.f));
    this->levelUpText.setScale(sf::Vector2f(0.7,0.7));

    this->secondText.setFillColor(sf::Color::Black);
    this->secondText.setCharacterSize(28);
    this->secondText.setString("Wybierz ulepszenie");
    this->secondText.setOrigin(sf::Vector2f(this->secondText.getGlobalBounds().size.x/2.f, this->secondText.getGlobalBounds().size.y/2.f));
    this->secondText.setScale(sf::Vector2f(0.7,0.7));

    upgradeText1.setCharacterSize(18);
    upgradeText2.setCharacterSize(18);
    upgradeText3.setCharacterSize(18);

    upgradeText1.setFillColor(sf::Color::White);
    upgradeText2.setFillColor(sf::Color::White);
    upgradeText3.setFillColor(sf::Color::White);
}

void UpgradeState::handleClick(sf::Vector2f mousePos) {
    if (button1.getGlobalBounds().contains(mousePos))
        selected = UpgradeChoice::First;
    else if (button2.getGlobalBounds().contains(mousePos))
        selected = UpgradeChoice::Second;
    else if (button3.getGlobalBounds().contains(mousePos))
        selected = UpgradeChoice::Third;
}

UpgradeChoice UpgradeState::getSelected() const {
    return selected;
}

void UpgradeState::resetSelection() {
    selected = UpgradeChoice::None;
}

void UpgradeState::setBorders() {
    this->border1.setTextureRect(sf::IntRect({64*8,0}, {64, 64}));
    this->border2.setTextureRect(sf::IntRect({64*8,0}, {64, 64}));
    this->border3.setTextureRect(sf::IntRect({64*8,0}, {64, 64}));

    this->border1.setScale(sf::Vector2f(2.f,2.f));
    this->border2.setScale(sf::Vector2f(2.f,2.f));
    this->border3.setScale(sf::Vector2f(2.f,2.f));

    this->border1.setOrigin(sf::Vector2f(this->border1.getLocalBounds().size.x/2.f, this->border1.getLocalBounds().size.y/2.f));
    this->border2.setOrigin(sf::Vector2f(this->border2.getLocalBounds().size.x/2.f, this->border2.getLocalBounds().size.y/2.f));
    this->border3.setOrigin(sf::Vector2f(this->border3.getLocalBounds().size.x/2.f, this->border3.getLocalBounds().size.y/2.f));
}

Upgrade UpgradeState::getUpgrade(UpgradeChoice choice) const {
    switch (choice) {
        case UpgradeChoice::First:  return upgrades[0];
        case UpgradeChoice::Second: return upgrades[1];
        case UpgradeChoice::Third:  return upgrades[2];
        default: return {UpgradeType::Speed, 0.f};
    }
}
