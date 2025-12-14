#include "../../include/game/Game.h"

// ******************* Initialization Methods Start *******************
void Game::initVariables() {
    /*
       @return void
       - Initialize all game variables
    */

    this->window = nullptr;

    // objects variables
    this->maxEnemies = 10;
    this->spawnInterval = 1.5f;
    this->velocityY = 20.f;
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
    this->screenSize = this->window->getSize();
}

void Game::initEnemies()
{
    this->spawnPositions = {
        {0.f, screenSize.y / 2.f},
        {screenSize.x / 2.f, 0.f},
        {static_cast<float>(screenSize.x), screenSize.y / 2.f},
        {screenSize.x / 2.f, static_cast<float>(screenSize.y)}
    };

    this->enemyTexture = std::make_shared<sf::Texture>();
    if (!enemyTexture->loadFromFile("../../assets/images/Orc-Walk.png"))
        throw std::runtime_error("Failed to load texture");

    this->spawnTimer = 0.f;
    this->spawnInterval = 1.5f;
}
// ******************* Initialization Methods End *******************

// ******************* Constructor/Destructor Start *******************
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();

    // ***INITIALIZE FAKE PLAYER TEXTURE FOR TESTING***
    sf::Vector2f screenCenter;
    screenCenter.x = this->screenSize.x / 2.f;
    screenCenter.y = this->screenSize.y / 2.f;
    this->rectangle.setSize({20.f, 80.f});
    this->rectangle.setOrigin(sf::Vector2f(10.f, 40.f));
    this->rectangle.setPosition(sf::Vector2f(screenCenter.x, screenCenter.y));
    this->rectangle.setFillColor(sf::Color::White);
    // ***INITIALIZE FAKE PLAYER TEXTURE FOR TESTING***
}

Game::~Game() {
    delete this->window;
}
// ******************* Constructor/Destructor Ends *******************

// ******************* Core Methods Start *******************
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
    updateRectPos(dt);

    // Update enemies
    sf::Vector2f playerPosition = this->rectangle.getPosition();
    updateEnemies(dt, playerPosition);
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
    for (auto const &enemy : enemies) {
        enemy->render(this->window);
    }

    // Draw test player entity
    this->window->draw(this->rectangle);

    this->window->display();
}
// ******************* Core Methods End *******************

// ******************* Other Methods Start *******************
void Game::updateRectPos(float dt) {
    /*
        @return void
        Temporary function to update position of fake player entity
    */

    float y = rectangle.getPosition().y;
    float x = this->rectangle.getPosition().x;
    y += velocityY * dt;
    x -= 20.f * dt;
    // if hit the edge -> change direction
    if(y <= 0.f) {
        y = 0.f;
        this->velocityY = std::abs(this->velocityY); // down
    } else if(y >= window->getSize().y - this->rectangle.getSize().y) {
        y = window->getSize().y - this->rectangle.getSize().y;
        this->velocityY = -std::abs(this->velocityY); // up
    }

    this->rectangle.setPosition(sf::Vector2f(x, y));
}

void Game::spawnEnemy() {
    /*
        @return void
        - Spawn signle enemy on rand spawn location if max enemy > current enemy count
    */

    if (this->enemies.size() >= this->maxEnemies) return;

    int randPosIdx = rand() % this->spawnPositions.size();

    sf::Vector2f offset{
        static_cast<float>((rand() % 200) - 80),
        static_cast<float>((rand() % 200) - 80)
    };

    this->enemies.push_back(
        std::make_unique<Enemy>(
            EnemyType::Basic,
            this->spawnPositions[randPosIdx] + offset,
            this->enemyTexture
        )
    );
}

void Game::updateEnemies(float dt, sf::Vector2f playerPosition) {
    /*
        @return void
        - Add timer to spawning enemy with time interval
    */
    this->spawnTimer += dt;

    if (this->spawnTimer >= this->spawnInterval)
    {
        spawnEnemy();
        spawnTimer = 0.f;
    }

    for (auto const &enemy : enemies)
        enemy->update(dt, playerPosition);
}
// ******************* Other Methods End *******************