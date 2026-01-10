#include "../include/game/Game.h"

int main()
{
    // Init srand seed
    srand(static_cast<unsigned>(time(nullptr)));

    const sf::Font font("assets/fonts/Cristone.ttf");

    // Init game engine
    Game game(font);

    // Start game
    game.run();

    return 0;
}