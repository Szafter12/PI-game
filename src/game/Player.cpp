#include "../../include/game/Player.h"
#include <cmath>

Player::Player(const sf::Vector2f position) {
    this->position = position;
    this->sprite.setPosition(this->position);
    this->ad = 20;

    this->guns_texture = std::make_shared<sf::Texture>();
    if (!this->guns_texture->loadFromFile("../../assets/images/all_guns.png")) {
        std::cout << "Failed to load guns texture" << std::endl;
    }

    this->arsenal.push_back(Weapon("Gun1", 0.5f, 20, 100.f, WeaponType::Gun1, this->guns_texture, sf::IntRect({0, 10}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun2", 0.4f, 25, 600.f, WeaponType::Gun2, this->guns_texture, sf::IntRect({30, 10}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun3", 1.5f, 60, 300.f, WeaponType::Gun3, this->guns_texture, sf::IntRect({58, 10}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun4", 0.3f, 25, 600.f, WeaponType::Gun4, this->guns_texture, sf::IntRect({86, 10}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun5", 1.3f, 50, 400.f, WeaponType::Gun5, this->guns_texture, sf::IntRect({118, 12}, {32, 16})));
    this->arsenal.push_back(Weapon("Gun6", 0.8f, 50, 250.f, WeaponType::Gun6, this->guns_texture, sf::IntRect({0, 28}, {32, 16})));

    this->sprite.setOrigin(sf::Vector2f(48.f/2.f, 64.f/2.f));
    this->sprite.setScale(sf::Vector2f(0.7, 0.7));
    this->lvl = {1};


    this->armor = {10};
    this->currentXp = {0};
    this->nextLvlCap = {100};
    this->speed = {70};

    plate.setFillColor(sf::Color(242, 158, 109,255));
    plate.setSize({100,32});
    plate.setOutlineColor(sf::Color(87, 46, 23,255));
    plate.setOutlineThickness(2);
    plate.setPosition({position.x-240,position.y+71});
}

void Player::update(const sf::RenderWindow &window, const float dt) {
    sf::Vector2f velocity(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num1)) switch_weapon(0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num2)) switch_weapon(1);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num3)) switch_weapon(2);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num4)) switch_weapon(3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num5)) switch_weapon(4);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num6)) switch_weapon(5);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num7)) switch_weapon(6);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num8)) switch_weapon(7);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num9)) switch_weapon(8);

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

    drawHpBar(window.getView());

    position = sprite.getPosition();
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (mousePos.y > position.y-16 &&
        mousePos.y < (position.y+16)) {
        if (mousePos.x < position.x) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mLeft.pause=false;mLeft.update();}
            else{ mLeft.pause=true;pauseAnim(3);sprite.setTexture(idleTxt);IdleLeft.pause=false;IdleLeft.update();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mRight.pause=false;mRight.update();}
            else{ mRight.pause=true;pauseAnim(4);sprite.setTexture(idleTxt);IdleRight.pause=false;IdleRight.update();}
        }
        }
    else if (mousePos.y < position.y-16) {
        if (mousePos.x < position.x-16) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;pauseAnim(1);sprite.setTexture(idleTxt);IdleUp.pause=false;IdleUp.update();}
        }
        else if (mousePos.x > position.x-16 &&
            mousePos.x < (position.x+16)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;pauseAnim(1);sprite.setTexture(idleTxt);IdleUp.pause=false;IdleUp.update();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mUp.pause=false;mUp.update();}
            else{ mUp.pause=true;pauseAnim(1);sprite.setTexture(idleTxt);IdleUp.pause=false;IdleUp.update();}
        }
    }
    else {
        if (mousePos.x < position.x-16) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;pauseAnim(2);sprite.setTexture(idleTxt);IdleDown.pause=false;IdleDown.update();}
        }
        else if (mousePos.x > position.x-16 &&
            mousePos.x < (position.x+16)) {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;pauseAnim(2);sprite.setTexture(idleTxt);IdleDown.pause=false;IdleDown.update();}
        }
        else {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)){ pauseAnim(0);sprite.setTexture(walkTxt);mDown.pause=false;mDown.update();}
            else{ mDown.pause=true;pauseAnim(2);sprite.setTexture(idleTxt);IdleDown.pause=false;IdleDown.update();}
        }
    }

    // this->initHitBoxOutline();
}

void Player::draw(sf::RenderWindow &window) const {
    window.draw(sprite);
    window.draw(plate);
    window.draw(hpBar);
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

bool Player::isLvlUp() const {
    return this->currentXp >= this->nextLvlCap;
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


void Player::drawHpBar(const sf::View &view) {
    constexpr float fullBar = 15;
    float hpRatio = static_cast<float>(this->hp) / static_cast<float>(maxHp);
    this->hpBar.setSize(sf::Vector2f(fullBar * hpRatio*6, 2.f*4));

    if (hpRatio > 0.75) {
        this->hpBar.setFillColor(sf::Color::Green);
    } else if (hpRatio > 0.30) {
        this->hpBar.setFillColor(sf::Color::Yellow);
    } else {
        this->hpBar.setFillColor(sf::Color::Red);
    }

    this->plate.setOrigin(sf::Vector2f(plate.getGlobalBounds().size.x/2.f, plate.getGlobalBounds().size.x/2.f));
    this->hpBar.setOrigin(sf::Vector2f(this->hpBar.getGlobalBounds().size.x/ 2.f, this->hpBar.getGlobalBounds().size.y / 2.f));
    plate.setPosition({view.getCenter().x,view.getCenter().y+150});
    this->hpBar.setPosition({view.getCenter().x-2.f,view.getCenter().y+115.f});
}

void Player::pauseAnim(int a) {
    if (a!=1) IdleUp.pause=true;
    if (a!=2) IdleDown.pause=true;
    if (a!=3) IdleLeft.pause=true;
    if (a!=4) IdleRight.pause=true;
}