#include "../../include/game/Player.h"

Player::Player(const sf::Vector2f position) {
    this->position = position;
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
    this->sprite.setOrigin(sf::Vector2f(48.f/2.f, 64.f/2.f));
    this->ad = {20};
    this->sprite.setScale(sf::Vector2f(0.7, 0.7));
    this->lvl = {1};
    this->armor = {10};
    this->currentXp = {0};
    this->nextLvlCap = {100};
}

void Player::update(const sf::RenderWindow &window) {
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

    if (mousePos.y > position.y-16 &&
        mousePos.y < (position.y+16)) {
        if (mousePos.x < position.x) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mLeft.pause=false;mLeft.update();}
            else{ mLeft.pause=true;mLeft.reset();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mRight.pause=false;mRight.update();}
            else{ mRight.pause=true;mRight.reset();}
        }
        }
    else if (mousePos.y < position.y-16) {
        if (mousePos.x < position.x-16) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;mUp.reset();}
        }
        else if (mousePos.x > position.x-16 &&
            mousePos.x < (position.x+16)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;mUp.reset();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;mUp.reset();}
        }
    }
    else {
        if (mousePos.x < position.x-16) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;mDown.reset();}
        }
        else if (mousePos.x > position.x-16 &&
            mousePos.x < (position.x+16)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;mDown.reset();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;mDown.reset();}
        }
    }
    // this->initHitBoxOutline();
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    // window.draw(hitBox);
}

sf::FloatRect Player::getBounds() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.size.x = bounds.size.x/3.f;
    bounds.size.y = bounds.size.y/2.f;
    bounds.position.x +=11.2f;
    bounds.position.y +=11.2f;
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

void Player::lvlUp() {
    if (this->currentXp >= this->nextLvlCap) {
        ++this->lvl;
        this->nextLvlCap += 100;
        this->currentXp = {0};
    }
}

void Player::getAttack() {

}
