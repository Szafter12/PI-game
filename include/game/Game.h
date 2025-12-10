#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Enemy.h"

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

    // Game logic
    // Game objects
    std::unique_ptr<Enemy> enemy;
    sf::RectangleShape rectangle;
    float velocityY = 60.f;
    // Resources

    // Private functions:
    void initVariables();
    void initWindow();
    void updateRectPos(float dt);
public:
    // Constructor / Destructor
    Game ();
    ~Game ();

    // Accessors
    void run();

    // Functions
    void pollEvents();
    void update(float dt);
    void render();
};

#endif //GAME_PI_GAME_H