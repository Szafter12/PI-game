#ifndef GAME_PI_GAMEPLAYSTATE_H
#define GAME_PI_GAMEPLAYSTATE_H

#include "State.h"
#include "StateManager.h"

class GameplayState : public State {
public:
    GameplayState(StateManager& sm, sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    StateManager& stateManager;
    sf::Font& font;
};


#endif //GAME_PI_GAMEPLAYSTATE_H