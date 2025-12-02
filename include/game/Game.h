#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>

#ifndef GAME_PI_GAME_H
#define GAME_PI_GAME_H

/*
Class that acts as the game engine
Wrapper class
*/

class Game final {
    // Variables:
    // Window
    sf::RenderWindow* window {};
    // Game logic
    // Game objects
    // Resources
    // Private functions:
    void initVariables();
    void initWindow();
public:
    // Constructor / Destructor
    Game ();
    ~Game ();
    // Accessors
    bool running() const;
    // Functions
    void pollEvents() const;
    void update() const;
    void render() const;
};

#endif //GAME_PI_GAME_H