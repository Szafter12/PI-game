#include "../../include/game/Player.h"

Player::Player(sf::Vector2f position) {
    texture[0].loadFromFile("../../assets/images/HeroIdleUp.png");
    texture[1].loadFromFile("../../assets/images/HeroIdleUpR.png");
    texture[2].loadFromFile("../../assets/images/HeroIdleR.png");
    texture[3].loadFromFile("../../assets/images/HeroIdleDownR.png");
    texture[4].loadFromFile("../../assets/images/HeroBase.png");
    texture[5].loadFromFile("../../assets/images/HeroIdleDownL.png");
    texture[6].loadFromFile("../../assets/images/HeroIdleL.png");
    texture[7].loadFromFile("../../assets/images/HeroIdleUpL.png");
    this->position = position;
    sprite.setTexture(texture[0]);
    sprite.setPosition(position);
}

void Player::update(sf::RenderWindow &window) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
        sprite.move({-1,0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
        sprite.move({1,0});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
        sprite.move({0,-1});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
        sprite.move({0,1});
    }

    position = sprite.getPosition();
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (mousePos.y > position.y &&
        mousePos.y < (position.y+sprite.getTexture().getSize().y)) {
        if (mousePos.x < position.x) sprite.setTexture(texture[6]);
        else sprite.setTexture(texture[2]);
        }
    else if (mousePos.y < position.y) {
        if (mousePos.x < position.x) sprite.setTexture(texture[7]);
        else if (mousePos.x > position.x &&
            mousePos.x < (position.x+sprite.getTexture().getSize().x)) sprite.setTexture(texture[0]);
        else sprite.setTexture(texture[1]);
    }
    else {
        if (mousePos.x < position.x) sprite.setTexture(texture[5]);
        else if (mousePos.x > position.x &&
            mousePos.x < (position.x+sprite.getTexture().getSize().x)) sprite.setTexture(texture[4]);
        else sprite.setTexture(texture[3]);
    }

    this->initHitBoxOutline();
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    window.draw(hitBox);
}

sf::FloatRect Player::getBounds() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return bounds;
}

void Player::initHitBoxOutline() {
    sf::FloatRect bounds = this->getBounds();

    this->hitBox.setPosition(sf::Vector2f(bounds.position.x, bounds.position.y));
    this->hitBox.setSize(sf::Vector2f(bounds.size.x, bounds.size.y));
    this->hitBox.setFillColor(sf::Color::Transparent);
    this->hitBox.setOutlineColor(sf::Color::Red);
    this->hitBox.setOutlineThickness(1.f);
}