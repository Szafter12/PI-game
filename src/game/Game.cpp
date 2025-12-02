#include "../../include/game/Game.h"

// Contructor / Desctructor
Game::Game()
{
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

// Init functions
void Game::initVariables() {
    this->window = nullptr;
}

void Game::initWindow() {
    this->window = new sf::RenderWindow (sf::VideoMode({640,480}), "Gierka PI", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

// Functions
bool Game::running() const {
    return this->window->isOpen();
}

void Game::pollEvents() const {
    while (const std::optional event = this->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->window->close();
        }
    }
}

void Game::update() const {
    this->pollEvents();
}

void Game::render() const {
    /*
        @return void
        - clear old frame
        - render objects
        - display frame in window
        Renders the game objects
    */

    this->window->clear();
    // Draw game objects
    this->window->display();
}

