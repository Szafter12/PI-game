#ifndef GAME_PI_GAME_H
#define GAME_PI_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Enemy.h"
#include "TileMap.h"
#include "Player.h"
#include "Bullet.h"
#include "states/UpgradeState.h"

/*
Class that acts as the game engine
Wrapper class
*/

class Game final {
    // Variables:
    sf::ContextSettings settings;
    sf::Font font;

    sf::Text pauseText;

    // Window
    sf::RenderWindow* window {};
    sf::Vector2f screenSize {};

    // Game logic
    int maxEnemies {};
    float spawnInterval {};
    TileMap hills;
    TileMap ground;
    TileMap water;
    TileMap border;
    float spawnTimer {0.f};
    bool isStopped {false};
    bool isLvlUp {false};
    UpgradeState upgradeState;

    // Game objects
    std::vector<sf::Vector2f> spawnPositions;
    std::shared_ptr<sf::Texture> enemyTexture;
    std::vector<std::unique_ptr<Enemy>> enemies;

    Player player = Player({0,0});
    sf::View view {};

    // Bullets
    std::vector<std::unique_ptr<Bullet>> bullets;

    sf::Texture bullet_texture;


    sf::Texture border_texture;
    sf::Sprite borderSprite;


    // Private functions:
    void initVariables();
    void initWindow();
    void updateBullets(float dt);
    void stopGame();
    void updatePauseText();

public:
    // Constructor / Destructor
    Game (const sf::Font &font_);
    ~Game ();

    // Accessors
    void run();

    // Core Methods
    void pollEvents();
    void update(float dt);
    void render();

    // Objects Methods
    void spawnEnemy(const sf::Vector2f playerPos);
    void updateEnemies(float dt, sf::Vector2f playerPosition);
};

#endif //GAME_PI_GAME_H