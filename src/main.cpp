#include "../include/game/Game.h"

int main()
{
    // Init srand seed
    srand(static_cast<unsigned>(time(nullptr)));

    // Init game engine
    const Game game;

    // Start game
    game.run();

    return 0;
}