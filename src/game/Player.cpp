#include "../../include/game/Player.h"

Player::Player(sf::Vector2f position) {
    this->position = position;
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
    this->sprite.setOrigin(sf::Vector2f(32.f/2.f, 32.f/2.f));
    this->ad = 20;

    this->guns_texture = std::make_shared<sf::Texture>();
    if (!this->guns_texture->loadFromFile("assets/images/all_guns.png")) {
        std::cout << "ERROR: Nie udalo sie zaladowac all_guns.png" << std::endl;
    }

    this->arsenal.push_back(Weapon("Gun1", 0.4f, 20, 500.f, WeaponType::Gun1, this->guns_texture, sf::IntRect({0, 5}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun2", 0.2f, 15, 700.f, WeaponType::Gun2, this->guns_texture, sf::IntRect({30, 5}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun3", 1.5f, 60, 300.f, WeaponType::Gun3, this->guns_texture, sf::IntRect({58, 5}, {32, 16})));
}

void Player::update(sf::RenderWindow &window) {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num1)) switch_weapon(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num2)) switch_weapon(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num3)) switch_weapon(2);


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
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mUpL.pause=false;mUpL.update();}
            else{ mUpL.pause=true;mUpL.reset();}
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
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mUpR.pause=false;mUpR.update();}
            else{ mUpR.pause=true;mUpR.reset();}
        }
    }
    else {
        if (mousePos.x < position.x-16) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mDownL.pause=false;mDownL.update();}
            else{ mDownL.pause=true;mDownL.reset();}
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
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ mDownR.pause=false;mDownR.update();}
            else{ mDownR.pause=true;mDownR.reset();}
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

void Player::getAttack() {

}

Weapon &Player::get_current_weapon() {
    if (arsenal.empty()) {
        static auto fallback = Weapon("Null", 1.f, 0, 0.f, WeaponType::Gun1, std::make_shared<sf::Texture>(), sf::IntRect({0, 0}, {0, 0}));
        return fallback;
    }
    return this->arsenal[this->weapon_index];
}

void Player::switch_weapon(int index) {
    if (index >= 0 && index < this->arsenal.size()) {
        this->weapon_index = index;
    }
}

