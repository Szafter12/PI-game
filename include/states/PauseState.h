#ifndef GAME_PI_PAUSESTATE_H
#define GAME_PI_PAUSESTATE_H

#include <SFML/Graphics.hpp>
#include "GameplayState.h"
#include "StateManager.h"
#include "State.h"


class PauseState : public State {
public:
    PauseState(StateManager& sm, sf::Font& font);

    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;

private:
    StateManager& stateManager;
    sf::Text text;
};

#endif //GAME_PI_PAUSESTATE_H