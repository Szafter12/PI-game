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
    this->obiekt.setPosition({0,0});
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

    // Update enemies
    sf::Vector2f playerPosition = this->player.position;

    updateEnemies(dt, playerPosition);
    this->player.update(*this->window);

    this->view.setCenter({player.position.x+16, player.position.y+16});
    this->window->setView(view);

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

    this->window->draw(obiekt);
    this->player.draw(*this->window);

    this->window->display();
}
// ******************* Core Methods End *******************

// ******************* Other Methods Start *******************

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

void Game::updateEnemies(const float dt, const sf::Vector2f playerPosition) {
    /*
        @return void
        - Add timer to spawning enemy with time interval
    */
    this->spawnTimer += dt;

    if (this->spawnTimer >= this->spawnInterval)
    {
        this->spawnEnemy();
        this->spawnTimer = 0.f;
    }

    for (auto const &enemy : enemies)
        enemy->update(dt, playerPosition);
}
// ******************* Other Methods End *******************