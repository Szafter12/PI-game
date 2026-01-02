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
    this->spawnInterval = 1.f;

    this->player.position = {this->screenSize.x / 2.f, this->screenSize.y / 2.f};

    hills.loadFromJsonLayer("../../assets/map/map.json", "Hills", "../../assets/map/spritesheet.png");
    ground.loadFromJsonLayer("../../assets/map/map.json", "Ground", "../../assets/map/spritesheet.png");
    water.loadFromJsonLayer("../../assets/map/map.json", "Water", "../../assets/map/spritesheet.png");
    border.loadFromJsonLayer("../../assets/map/map.json", "Border", "../../assets/map/spritesheet.png");
}

void Game::initWindow() {
    /*
       @return void
       - Initialize starting window
       - Adding default options
   */
    this->window = new sf::RenderWindow (sf::VideoMode({1920,1080}), "Gierka PI", sf::Style::Default, sf::State::Fullscreen, settings);
    this->window->setFramerateLimit(60);
    this->screenSize.x = this->window->getSize().x;
    this->screenSize.y = this->window->getSize().y;

    this->view = sf::View({this->player.position.x, this->player.position.y}, {this->screenSize.x, this->screenSize.y});
    this->view.zoom(0.25);
}
// ******************* Initialization Methods End *******************

// ******************* Constructor/Destructor Start *******************
Game::Game(const sf::Font &font_) : font(font_), pauseText(font), upgradeState(&this->font)
{
    this->initVariables();
    this->initWindow();
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
        dt = std::min(dt, 0.05f);
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
        } else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
                if (this->isStopped) {
                    this->isStopped = false;
                } else {
                    this->isStopped = true;
                }
            }
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

    sf::Vector2f playerPosition = this->player.position;
    if (!this->isStopped && !this->isLvlUp) {
        // Update enemies
        this->updateEnemies(dt, playerPosition);

        // Update bullets
        this->updateBullets(dt);
        this->player.update(*this->window, dt);

        for (const auto &enemy: this->enemies) {
            enemy->collideWithPlayer(player, dt);
        }
    }

    if (this->isLvlUp) this->upgradeState.update(dt, playerPosition);
    if (this->isStopped) this->updatePauseText();

    view.setCenter(view.getCenter() +
    (playerPosition - view.getCenter()) * 10.f * dt);
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
    this->window->draw(this->water);
    this->window->draw(this->border);
    this->window->draw(this->ground);
    this->window->draw(this->hills);

    for (auto const &enemy : enemies) {
        enemy->render(this->window);
    }
    for (auto const &bullet : bullets) {
        bullet->render(*this->window);
    }

    this->player.draw(*this->window);

    if (this->isLvlUp) {
        this->upgradeState.draw(*this->window);
    }

    if (this->isStopped) {
        this->window->draw(this->pauseText);
    }

    this->window->display();
}
// ******************* Core Methods End *******************

// ******************* Other Methods Start *******************

void Game::spawnEnemy(const sf::Vector2f playerPos) {
    /*
        @return void
        - Spawn signle enemy on rand spawn location if max enemy > current enemy count
    */

    this->spawnPositions = {
        // left
        { playerPos.x - screenSize.x / 2.f, playerPos.y },

        // up
        { playerPos.x, playerPos.y - screenSize.y / 2.f },

        // right
        { playerPos.x + screenSize.x / 2.f, playerPos.y },

        // down
        { playerPos.x, playerPos.y + screenSize.y / 2.f }
    };

    if (this->enemies.size() >= this->maxEnemies) return;

    int randPosIdx = rand() % this->spawnPositions.size();

    sf::Vector2f offset{
        static_cast<float>((rand() % 50) - 10),
        static_cast<float>((rand() % 50) - 10)
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
        this->spawnEnemy(playerPosition);
        this->spawnTimer = 0.f;
    }

    for (auto const &enemy : enemies)
        enemy->update(dt, playerPosition);

    for (int i = 0 ; i < this->enemies.size(); i++) {
        if (!enemies[i]->is_alive()) {
            player.currentXp += enemies[i]->xp;
            enemies.erase(enemies.begin() + i);
            if (player.isLvlUp()) {
                player.lvlUp();
                this->isLvlUp = {true};
                this->maxEnemies += 20;
            } else {
                this->isLvlUp = {false};
            }
        }
    }

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

        auto bullet_bounds = this->bullets[i]->getGlobalBounds();

        for (int j = 0; j < this->enemies.size(); j++) {
            if (bullet_bounds.findIntersection(this->enemies[j]->getBounds())) {
                enemies[j]->getAttack(player.ad, Weapons(player.weapon));
                this->bullets.erase(this->bullets.begin() + i);
                i--;
                break;
            }
        }
    }
}

void Game::stopGame() {
    this->isStopped = true;
}

void Game::updatePauseText() {
    this->pauseText.setString("Pause");
    pauseText.setCharacterSize(68);
    sf::FloatRect pauseBounds = pauseText.getGlobalBounds();
    pauseText.setOrigin(sf::Vector2f(pauseBounds.size.x / 2, pauseBounds.size.y / 2));
    pauseText.setPosition(sf::Vector2f(this->player.position.x, this->player.position.y - 50.f));
    pauseText.setFillColor(sf::Color::Black);
}

// ******************* Other Methods End *******************