#include "../include/game/Game.h"

int main()
{
    // Init srand seed
    srand(static_cast<unsigned>(time(nullptr)));

    // Init game engine
    const Game game;

    // Game loop
    while (game.running()) {
        // Update
        game.update();
        // Render
        game.render();
    }

    return 0;
}