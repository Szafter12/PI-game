#ifndef GAME_PI_STATEMANAGER_H
#define GAME_PI_STATEMANAGER_H

#include <SFML/Graphics.hpp>
#include "State.h"

class StateManager {
public:
    void changeState(std::unique_ptr<State> state);
    void handleEvent(const sf::Event& event) const;
    void update(float dt) const;
    void draw(sf::RenderWindow& window) const;

private:
    std::unique_ptr<State> currentState;
};


#endif //GAME_PI_STATEMANAGER_H