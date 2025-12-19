#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Enemy.h"

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

    // Game objects
    std::vector<sf::Vector2f> spawnPositions;
    std::vector<std::unique_ptr<Enemy>> enemies;

    ////////////////////////////////Zmienne testowe
    Player player = Player({0,0});
    sf::View view {};
    //////////////////////////////////

    // Private functions:
    void initVariables();
    void initWindow();
    void initEnemies();
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