#ifndef GAME_PI_GAME_H
#define GAME_PI_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "CollisionMap.h"
#include <ctime>
#include <cstdlib>
#include "Enemy.h"
#include "TileMap.h"
#include "Player.h"
#include "Bullet.h"
#include "Button.h"
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

    int room=0;
    CollisionMap collisionMap;
    // Game logic

    // Enemies
    int maxEnemies {};
    int currentEnemies {};
    float spawnInterval {};

    // Game logic
    TileMap trees;
    TileMap borders;
    TileMap walls;
    TileMap upupground;
    TileMap upground;
    TileMap ground;
    TileMap water;
    TileMap bridges;
    float spawnTimer {0.f};
    bool isStopped {false};
    bool isGameOver {false};
    bool isLvlUp {false};

    bool soundOn=true;
    bool musicOn=true;

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

    sf::Texture titleTexture = sf::Texture("../../assets/images/tytul.png");
    sf::Sprite titleSprite = sf::Sprite(titleTexture);

    Button resumeB = Button("Wznow",{100,-100},{130,40}),
    menuB = Button("Menu glowne",{100,60},{130,40}),
    saveB = Button("Zapisz",{100,-20},{130,40}),
    loadB = Button("Wczytaj gre",{-80,80},{130,40}),
    newB = Button("Nowa gra",{-80,20},{130,40}),
    settingsB = Button("Ustawienia",{80,20},{130,40}),
    exitB = Button("Wyjdz",{80,80},{130,40}),
    soundB = Button("Dzwiek:On",{0,-40},{130,40}),
    musicB = Button("Muzyka:On",{0,20},{130,40}),
    returnB = Button("Powrot",{0,80},{130,40});

    // Private functions:
    void initVariables();
    void initWindow();
    void updateBullets(float dt);
    void stopGame();
    void updatePauseText();
    bool isWaveClear() const;
    void handlePlayerTileCollisions();
    void gameOver();

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

    void loadSave();
    void saveGame();
};

#endif //GAME_PI_GAME_H