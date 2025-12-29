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

    this->player.position = {this->screenSize.x / 2.f, this->screenSize.y / 2.f};
    this->view = sf::View({this->player.position.x, this->player.position.y}, {400.f, 300.f});

    constexpr std::array level = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };

    // create the tilemap from the level definition

    if (!map.load("tileset.png", {32, 32}, level.data(), 16, 8))
    {std::cout<<"error loading tileset.png"<<std::endl;}
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

    this->updateEnemies(dt, playerPosition);
    // Update bullets
    this->updateBullets(dt);
    updateEnemies(dt, playerPosition);
    this->player.update(*this->window);

    for (auto &enemy: this->enemies) {
        enemy->collideWithPlayer(player, dt);
    }

    this->view.setCenter({player.position.x, player.position.y});
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
  this->window->draw(map);
    // Draw game objects
    for (auto const &enemy : enemies) {
        enemy->render(this->window);
    }
    for (auto const &bullet : bullets) {
        bullet->render(*this->window);
    }
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
            this->spawnPositions[randPosIdx] + offset)
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

    for (size_t i = 0; i < enemies.size(); ++i) {
        for (size_t j = i + 1; j < enemies.size(); ++j) {
            enemies[i]->checkCollisionWithOtherEnemies(*enemies[j], dt);
        }
    }
}

void Game::updateBullets(float dt) {

    static float shoot_timer = 0.f;
    shoot_timer += dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && shoot_timer > 0.3f) {
        shoot_timer = 0.f;

        // Mouse position
        sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

        this->bullets.push_back(std::make_unique<Bullet>(
            this->player.position,
            mouse_position
            ));
    }

    for (int i = 0; i < this->bullets.size(); i++) {
        this->bullets[i]->update(dt);

        if (this->bullets[i]->isDead()) {
            this->bullets.erase(this->bullets.begin() + i);
            i--;
            continue;
        }

        bool hit = false;
        auto bullet_bounds = this->bullets[i]->getGlobalBounds();

        for (int j = 0; j < this->enemies.size(); j++) {
            if (bullet_bounds.findIntersection(this->enemies[j]->getBounds())) {
                this->enemies.erase(this->enemies.begin() + j);
                hit = true;
                break;
            }
        }

        if (hit) {
            this->bullets.erase(this->bullets.begin() + i);
            i--;
        }
    }
}
// ******************* Other Methods End *******************