#include "../../include/game/Game.h"

// Contructor / Desctructor
Game::Game()
{
    this->initVariables();
    this->initWindow();

    // ***INITIALIZE FAKE PLAYER TEXTURE FOR TESTING***
    sf::Vector2u screenSize = this->window->getSize();
    sf::Vector2f screenCenter;
    screenCenter.x = screenSize.x / 2.f;
    screenCenter.y = screenSize.y / 2.f;
    this->rectangle.setSize({20.f, 80.f});
    this->rectangle.setOrigin(sf::Vector2f(10.f, 40.f));
    this->rectangle.setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
    this->rectangle.setFillColor(sf::Color::White);
    // ***INITIALIZE FAKE PLAYER TEXTURE FOR TESTING***

    // Test enemy init
    auto enemyTexture = std::make_shared<sf::Texture>();
    if (!enemyTexture->loadFromFile("../../assets/images/Orc-Walk.png")) {
        throw std::runtime_error("Failed to load texture");
    }
    enemy = std::make_unique<Enemy>(EnemyType::Basic, sf::Vector2f(500.f, 100.f), enemyTexture);
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
void Game::run() {
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

void Game::pollEvents() {
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

void Game::update(float dt) {
    /*
        @return void
        - update game elements
        - frames per seconds time
    */

    this->pollEvents();
    // test player position
    sf::Vector2f playerPosition = this->rectangle.getPosition();

    enemy->update(dt, playerPosition);
}

void Game::render() {
    /*
        @return void
        - clear old frame
        - render objects
        - display frame in window
        Renders the game objects
    */

    this->window->clear();
    // Draw game objects
    if (enemy) {
        enemy->render(this->window);
    }
    this->window->draw(this->rectangle);
    this->window->display();
}

