#ifndef GAME_PI_ENEMY_H
#define GAME_PI_ENEMY_H
#include "SFML/Audio/Sound.hpp"

class Player;
class Collider;
class DamageCalculator;

#include <SFML/Graphics.hpp>
#include "Weapons.h"

inline constexpr double PI = 3.14159265359;

enum class EnemyType {
    Basic
};

enum class EnemyState {
    Run,
    Attack
};

enum class EnemyDirection {
    Down = 0,
    Up = 1,
    Left = 2,
    Right = 3,
};

class Enemy {
private:
    // Private properties

    // Texture
    // sf::Texture textureRun = {sf::Texture("../../assets/images/test_enemy.png")};
    // sf::Texture textureAttack = {sf::Texture("../../assets/images/enemy_attack.png")};
    sf::Texture textureRun = {sf::Texture("../../assets/images/test_enemy.png")};
    sf::Texture textureAttack = {sf::Texture("../../assets/images/enemy_attack.png")};

    // Position
    float scale{};
    EnemyDirection direction = EnemyDirection::Down;
    EnemyDirection lastDirection = direction;
    sf::RectangleShape hitBox;

    // animations
    EnemyState state = EnemyState::Run;
    int frame{0};
    float frameTime{0.f};
    float frameDuration = {0.2f};
    float frameDurationAttack = {0.3f};
    bool isAttacking = false;

    // Private methods
    void updateAnimation(float dt);
    void updatePosition(float dt, sf::Vector2f playerPosition);
    void enemyChangeTexture();
    void initHitBoxOutline();
    void startAttack();
    void setState(EnemyState newState);
    void resetAnimation();
    void drawHpBar();

public:
    // Public properties

    // stats
    float speed {};
    sf::Vector2f position{};
    float maxHp {};
    float hp {};
    int xp {};
    sf::RectangleShape hpBar {};
    int armor {};
    int ad {};
    sf::Vector2f velocity;

    // Sprite
    sf::Sprite sprite;

    // Constructor/Destructor
    Enemy(EnemyType type, sf::Vector2f position_);

    // Core Methods
    void update(float dt, sf::Vector2f playerPosition);
    void render(sf::RenderTarget *target) const;

    // Other Methods
    sf::FloatRect getBounds() const;
    void checkCollisionWithOtherEnemies(Enemy &other, float dt);
    sf::Vector2f getPosition() const;
    void collideWithPlayer(Player &player, float dt, bool snd, sf::Sound *sound);
    bool is_alive() const;
    void getAttack(int ad);
};
#endif //GAME_PI_ENEMY_H