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
    /*
       @return void
       - Initialize all game variables
   */
    this->window = nullptr;
}
void Game::initWindow() {
    /*
       @return void
       - Initialize starting window
       - Adding default options
   */
    this->settings.antiAliasingLevel = 8;
    this->window = new sf::RenderWindow (sf::VideoMode({640,480}), "Gierka PI", sf::Style::Default, sf::State::Windowed, settings);
    this->window->setFramerateLimit(60);
}

// Functions
void Game::run() const {
    /*
       @return void
       - Starting game loop
       - initialize delta time to ensure game work same on diffrent fps
       - Call update and render functions every fps
   */
    sf::Clock clock;
    while (this->window->isOpen()) {
        float dt = clock.restart().asSeconds();
        update(dt);
        render();
    }
}

void Game::pollEvents() const {
    /*
        @return void
        - Waiting for some events such as close window
    */

    while (const std::optional event = this->window->pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            this->window->close();
        }
    }
}

void Game::update(float dt) const {
    /*
        @return void
        - update game elements
        - frames per seconds time
    */

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

