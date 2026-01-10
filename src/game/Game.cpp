#include "../../include/game/Game.h"
#include "windows.h"

// ******************* Initialization Methods Start *******************
void Game::initVariables() {
    /*
       @return void
       - Initialize all game variables
    */

    this->window = nullptr;

    titleSprite.setOrigin({titleSprite.getLocalBounds().size.x / 2, titleSprite.getLocalBounds().size.y / 2});
    titleSprite.setPosition({0,-60});
    // objects variables
    this->maxEnemies = {10};
    this->currentEnemies = {0};
    this->spawnInterval = {1.f};

    this->player.position = {this->screenSize.x / 2.f, this->screenSize.y / 2.f};

    if (!this->bullet_texture.loadFromFile("../../assets/images/bullet.png")) {
        std::cout << "Failed to load bullet texture" << std::endl;
    }
    if (!this->border_texture.loadFromFile("../../assets/images/border.png")) {
        std::cout << "Failed to load border texture" << std::endl;
    }

    this->borderSprite.setTexture(this->border_texture);
    this->borderSprite.setTextureRect(sf::IntRect({0, 0}, {64, 64}));
    this->borderSprite.setScale({0.5, 0.5});
    this->borderSprite.setPosition({10.f, 40.f});

    bridges.loadFromJsonLayer("../../assets/map/map.json", "bridges", "../../assets/map/spritesheet.png");
    upupground.loadFromJsonLayer("../../assets/map/map.json", "upupground", "../../assets/map/spritesheet.png");
    trees.loadFromJsonLayer("../../assets/map/map.json", "trees", "../../assets/map/spritesheet.png");
    borders.loadFromJsonLayer("../../assets/map/map.json", "borders", "../../assets/map/spritesheet.png");
    walls.loadFromJsonLayer("../../assets/map/map.json", "walls", "../../assets/map/spritesheet.png");
    ground.loadFromJsonLayer("../../assets/map/map.json", "ground", "../../assets/map/spritesheet.png");
    water.loadFromJsonLayer("../../assets/map/map.json", "water", "../../assets/map/spritesheet.png");
    upground.loadFromJsonLayer("../../assets/map/map.json", "upground", "../../assets/map/spritesheet.png");
    ground.loadCollisionLayer("../../assets/map/map.json", "walls");
    ground.loadCollisionLayer("../../assets/map/map.json", "water");
    ground.loadCollisionLayer("../../assets/map/map.json", "trees");
    ground.loadCollisionLayer("../../assets/map/map.json", "upupground");

    ground.removeCollisions("../../assets/map/map.json", "bridges");

    std::set<std::string> blockingLayers = { "walls", "trees", "water", "upupground", "borders" };

    // Lista rzeczy, które pozwalają chodzić NAWET jak pod spodem jest blokada (mosty)
    std::set<std::string> walkableLayers = { "bridges" };

    collisionMap.loadFromSpriteFusion(
        "../../assets/map/map.json",
        blockingLayers,
        walkableLayers
    );
    sf::Vector2f mapSize = ground.getSize();
    sf::Vector2f centerPos = { mapSize.x / 2.f, mapSize.y / 2.f };
    this->player.position = centerPos;
    this->player.sprite.setPosition(centerPos);
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
Game::Game(const sf::Font &font_) : font(font_), pauseText(font), upgradeState(&this->font), borderSprite(this->border_texture) {
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
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                if (this->isStopped) {
                    this->isStopped = false;
                } else {
                    this->isStopped = true;
                }
            }
            if (keyPressed->scancode == sf::Keyboard::Scancode::P) {
                this->window->close();
            }
        } else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouse->button == sf::Mouse::Button::Left && isLvlUp) {
                sf::Vector2f mousePos =
                    window->mapPixelToCoords(sf::Mouse::getPosition(*window));

                upgradeState.handleClick(mousePos);
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

    if (room==0) {
        this->window->setView(view);
        titleSprite.setPosition(window->getView().getCenter()+sf::Vector2f{0,-60});

        loadB.update(*this->window);
        if (loadB.isClicked) {
            enemies.clear();
            bullets.clear();
            loadSave();
        }

        newB.update(*this->window);
        if (newB.isClicked) {
            isStopped=false;
            isGameOver=false;
            sf::Vector2f mapSize = ground.getSize();
            sf::Vector2f centerPos = { mapSize.x / 2.f, mapSize.y / 2.f };
            this->player.position = centerPos;
            this->player.sprite.setPosition(centerPos);
            player.currentXp=0;
            player.lvl=1;
            player.maxHp=100;
            player.hp=player.maxHp;
            player.ad=20;
            player.armor = {10};
            player.nextLvlCap = {30};
            player.speed = {70};
            player.switch_weapon(0);

            enemies.clear();
            bullets.clear();

            room=1;
        }

        settingsB.update(*this->window);
        if (settingsB.isClicked) {Sleep(100);room=2;}

        exitB.update(*this->window);
        if (exitB.isClicked) this->window->close();
    }
    else if (room==1) {
        if (!this->isGameOver) {
            sf::Vector2f playerPosition = this->player.position;
            if (!this->isStopped && !this->isLvlUp) {
                // Update enemies
                this->updateEnemies(dt, playerPosition);

                // Update bullets
                this->updateBullets(dt);

                view.setCenter(view.getCenter() +
                (playerPosition - view.getCenter()));
                this->window->setView(view);

                this->player.update(*this->window, dt);

                this->handlePlayerTileCollisions();

                for (const auto &enemy: this->enemies) {
                    enemy->collideWithPlayer(player, dt);
                }
            }

    if (isLvlUp) {
        upgradeState.update(dt, player.position);

        UpgradeChoice choice = upgradeState.getSelected();
        if (choice != UpgradeChoice::None) {
            Upgrade upgrade = upgradeState.getUpgrade(choice);
            player.applyUpgrade(upgrade);

            isLvlUp = false;
            upgradeState.resetSelection();
        }
    }

    if (this->isStopped) this->updatePauseText();
            if (this->isStopped) {
                resumeB.update(*this->window);
                if (resumeB.isClicked) isStopped=false;

                menuB.update(*this->window);
                if (menuB.isClicked) {Sleep(2000);room=0;}

                saveB.update(*this->window);
                if (saveB.isClicked) saveGame();
            }

            view.setCenter(view.getCenter() +
            (playerPosition - view.getCenter()) * 10.f * dt);
            this->window->setView(view);

            this->borderSprite.setPosition({view.getCenter().x - 220.f, view.getCenter().y + 100.f});
            if (player.hp<=0) isGameOver = true;
        }
        else {
            gameOver();
            menuB.update(*this->window);
            if (menuB.isClicked) {Sleep(2000);room=0;}

            loadB.update(*this->window);
            if (loadB.isClicked) {
                enemies.clear();
                bullets.clear();
                loadSave();
            }
        }
    }
    else if (room==2) {
        soundB.update(*this->window);
        if (soundB.isClicked) {
            if (soundOn) {
                soundOn = false;
                soundB.label="Dzwiek:Off";
            }
            else {
                soundOn = true;
                soundB.label="Dzwiek:On";
            }
            Sleep(100);
        }

        musicB.update(*this->window);
        if (musicB.isClicked) {
            if (musicOn) {
                musicOn = false;
                musicB.label="Muzyka:Off";
            }
            else {
                 musicOn = true;
                 musicB.label="Muzyka:On";
            }
            Sleep(100);
        }
        returnB.update(*this->window);
        if (returnB.isClicked) {room=0;Sleep(100);}
    }
}

void Game::render() {
    /*
        @return void
        - clear old frame
        - render objects
        - display frame in window
        Renders the game objects
    */

    if (room==0) { //main menu
        this->window->clear();
        window->draw(titleSprite);
        loadB.draw(*this->window);
        newB.draw(*this->window);
        settingsB.draw(*this->window);
        exitB.draw(*this->window);
    }
    else if (room==1) {
        //level
        this->window->clear(sf::Color::Cyan);
        // Draw game objects
        this->window->draw(this->ground);
        this->window->draw(this->upground);
        this->window->draw(this->water);
        this->window->draw(this->walls);
        this->window->draw(this->upupground);
        this->window->draw(this->trees);
        this->window->draw(this->bridges);

    // sf::RectangleShape dbg;
    // // dbg.setFillColor(sf::Color::Transparent);
    // // // dbg.setOutlineColor(sf::Color::Red);
    // dbg.setOutlineThickness(1.f);
    //
    // for (const auto& c : collisionMap.getColliders())
    // {
    //     dbg.setPosition({c.position.x, c.position.y});
    //     dbg.setSize({c.size.x, c.size.y});
    //     window->draw(dbg);
    // }

        for (auto const &enemy : enemies) {
            enemy->render(this->window);
        }
        for (auto const &bullet : bullets) {
            bullet->render(*this->window);
        }

        // sf::Sprite weapon_icon = this->player.get_current_weapon().icon;
        // weapon_icon.setPosition({20.f, 20.f});
        // this->window->draw(weapon_icon);

        this->player.draw(*this->window);

        if (this->isLvlUp) {
            this->upgradeState.draw(*this->window);
        }

        //this->window->setView(this->window->getDefaultView());
        this->window->draw(this->borderSprite);
        sf::Sprite weaponIcon = this->player.get_current_weapon().icon;
        sf::FloatRect border_boudns = this->borderSprite.getGlobalBounds();
        sf::FloatRect weapon_bounds = weaponIcon.getGlobalBounds();

        float x = border_boudns.position.x + (border_boudns.size.x / 2.f) - (weapon_bounds.size.x / 2.f);
        float y = border_boudns.position.y + (border_boudns.size.y / 2.f) - (weapon_bounds.size.y / 2.f);


        weaponIcon.setPosition({x, y});
        this->window->draw(weaponIcon);

        if (isStopped && !isGameOver) {
            resumeB.draw(*this->window);
            saveB.draw(*this->window);
            menuB.position={100,60};
            menuB.draw(*this->window);
        }

        if (isGameOver) {
            window->draw(pauseText);
            loadB.draw(*this->window);
            menuB.position={80,80};
            menuB.draw(*this->window);
        }
    }
    else if (room==2) {
        this->window->clear();
        soundB.draw(*this->window);
        musicB.draw(*this->window);
        returnB.draw(*this->window);
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

    for (int i = 0; i < this->maxEnemies; i++) {
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
}

void Game::updateEnemies(const float dt, const sf::Vector2f playerPosition) {
    /*
        @return void
        - Add timer to spawning enemy with time interval
    */

    if (this->isWaveClear()) {
        this->currentEnemies = this->maxEnemies;
        this->spawnEnemy(playerPosition);
    }

    for (auto const &enemy : enemies) {
        enemy->update(dt, playerPosition);

        for (const auto& wallRect : this->ground.m_collisions) {
            sf::FloatRect enemyBounds = enemy->getBounds();
            sf::FloatRect wallBounds = this->ground.getTransform().transformRect(wallRect);

            auto intersection = enemyBounds.findIntersection(wallBounds);
            if (intersection) {
                if (intersection->size.x < intersection->size.y) {
                    if (enemyBounds.position.x < wallBounds.position.x)
                        enemy->position.x -= intersection->size.x;
                    else
                        enemy->position.x += intersection->size.x;
                }
                else {
                    if (enemyBounds.position.y < wallBounds.position.y)
                        enemy->position.y -= intersection->size.y;
                    else
                        enemy->position.y += intersection->size.y;
                }
                enemy->sprite.setPosition(enemy->position);
            }

        }
    }


    for (int i = 0 ; i < this->enemies.size(); i++) {
        if (!enemies[i]->is_alive()) {
            player.currentXp += enemies[i]->xp;
            enemies.erase(enemies.begin() + i);
            this->currentEnemies--;
            if (player.isLvlUp()) {
                player.lvlUp();
                this->isLvlUp = {true};
                this->maxEnemies += 20;
                upgradeState.rollUpgrades();
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

    Weapon& current_weapon = this->player.get_current_weapon();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space) && shoot_timer > current_weapon.fire_rate) {
        shoot_timer = 0.f;

        // Mouse position
        sf::Vector2f mouse_position = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

        this->bullets.push_back(std::make_unique<Bullet>(
            this->player.position,
            mouse_position,
            this->bullet_texture
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
                this->enemies[j]->getAttack(current_weapon.damage);

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
void Game::handlePlayerTileCollisions()
{
    sf::FloatRect playerBounds = player.getBounds();

    for (const auto& tile : collisionMap.getColliders())
    {
        if (playerBounds.findIntersection(tile))
        {
            player.revertPosition();
            return;
        }
    }
}

void Game::gameOver() {
    this->pauseText.setString("Koniec gry");
    pauseText.setCharacterSize(68);
}
void Game::updatePauseText() {
    this->pauseText.setString("Pause");
    pauseText.setCharacterSize(48);
    sf::FloatRect pauseBounds = pauseText.getGlobalBounds();
    pauseText.setOrigin(sf::Vector2f(pauseBounds.size.x / 2, pauseBounds.size.y / 2));
    pauseText.setPosition(sf::Vector2f(this->player.position.x, this->player.position.y - 50.f));
    pauseText.setFillColor(sf::Color::Black);

}

void Game::loadSave() {
    std::ifstream file("../../assets/save.txt");
    if (file.is_open() && file.peek() != std::ifstream::traits_type::eof()) {
        file>>player.lvl;
        file>>player.hp;
        file>>player.maxHp;
        file>>player.ad;
        file>>player.armor;
        file>>player.speed;
        file>>player.currentXp;
        file>>player.nextLvlCap;
        file>>player.position.x;
        file>>player.position.y;
        isGameOver=false;
        isStopped=false;
        room=1;
    }
    file.close();
}

void Game::saveGame() {
    std::ofstream file("../../assets/save.txt");
    if (file.is_open()) {
        file<<player.lvl;
        file<<" ";
        file<<player.hp;
        file<<" ";
        file<<player.maxHp;
        file<<" ";
        file<<player.ad;
        file<<" ";
        file<<player.armor;
        file<<" ";
        file<<player.speed;
        file<<" ";
        file<<player.currentXp;
        file<<" ";
        file<<player.nextLvlCap;
        file<<" ";
        file<<player.position.x;
        file<<" ";
        file<<player.position.y;
        /*file<<"\n";
        for (int i = 0; i < this->enemies.size(); i++) {
            file<<enemies[i]->position;
        }*/
        MessageBox(NULL,"Zapisano gre", "",MB_OK);
    }
    file.close();
}

bool Game::isWaveClear() const {
    return this->currentEnemies == 0;
}

// ******************* Other Methods End *******************
