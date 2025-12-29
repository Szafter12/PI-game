#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Enemy.h"
#include "map.h"
#include "Player.h"

#ifndef GAME_PI_GAME_H
#define GAME_PI_GAME_H

/*
Class that acts as the game engine
Wrapper class
*/

class Game final {
    // Variables:
    sf::ContextSettings settings;

    // Window
    sf::RenderWindow* window {};
    sf::Vector2u screenSize {};

    // Game logic
    int maxEnemies {};
    float spawnInterval {};
    float spawnTimer;
    Map map;
    // Game objects
    std::vector<sf::Vector2f> spawnPositions;
    std::shared_ptr<sf::Texture> enemyTexture;
    std::vector<std::unique_ptr<Enemy>> enemies;

    ////////////////////////////////Zmienne testowe
    Player player = Player({800,600});
    sf::Texture texture = sf::Texture("../../assets/images/map.png");
    sf::Sprite obiekt = sf::Sprite(texture);
    sf::View view = sf::View({player.position.x+16, player.position.y+16}, {400.f, 300.f});
    //////////////////////////////////

    // Resources

    // Test player rectangle
    //sf::RectangleShape rectangle;
    //float velocityY = {};

    // Private functions:
    void initVariables();
    void initWindow();
    void initEnemies();
    void updateRectPos(float dt);
public:
    // Constructor / Destructor
    Game ();
    ~Game ();

    // Accessors
    void run();

    // Core Methods
    void pollEvents();
    void update(float dt);
    void render();

    // Objects Methods
    void spawnEnemy();
    void updateEnemies(float dt, sf::Vector2f playerPosition);
};

#endif //GAME_PI_GAME_H