#include "../../include/game/Player.h"
#include <cmath>

Player::Player(const sf::Vector2f position) {
    this->position = position;
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->position);
    this->ad = 20;

    this->guns_texture = std::make_shared<sf::Texture>();
    if (!this->guns_texture->loadFromFile("assets/images/all_guns.png")) {
        std::cout << "ERROR: Nie udalo sie zaladowac all_guns.png" << std::endl;
    }

    this->arsenal.push_back(Weapon("Gun1", 0.4f, 20, 500.f, WeaponType::Gun1, this->guns_texture, sf::IntRect({0, 5}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun2", 0.2f, 15, 700.f, WeaponType::Gun2, this->guns_texture, sf::IntRect({30, 5}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun3", 1.5f, 60, 300.f, WeaponType::Gun3, this->guns_texture, sf::IntRect({58, 5}, {32, 16})));
    this->sprite.setOrigin(sf::Vector2f(48.f/2.f, 64.f/2.f));
    this->sprite.setScale(sf::Vector2f(0.7, 0.7));
    this->lvl = {1};
    this->armor = {10};
    this->currentXp = {0};
    this->nextLvlCap = {100};
    this->speed = {70};
}




void Player::update(const sf::RenderWindow &window, const float dt) {
    sf::Vector2f velocity(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num1)) switch_weapon(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num2)) switch_weapon(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num3)) switch_weapon(2);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        velocity.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        velocity.x += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W))
        velocity.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S))
        velocity.y += speed;

    if (velocity.x != 0.f || velocity.y != 0.f) {
        float len = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        velocity /= len;
        velocity *= speed;
    }

    position += velocity * dt;
    sprite.setPosition(position);

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
    ++this->lvl;
    this->nextLvlCap += 100;
    this->currentXp = {0};
}

bool Player::isLvlUp() {
    return this->currentXp >= this->nextLvlCap;
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


