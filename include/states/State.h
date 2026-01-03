#ifndef GAME_PI_STATE_H
#define GAME_PI_STATE_H

#include <SFML/Graphics.hpp>

class State {
public:
    virtual ~State() = default;
    virtual void handleEvent(const sf::Event&) = 0;
    virtual void update(float) = 0;
    virtual void draw(sf::RenderWindow&) const = 0;
};


#endif //GAME_PI_STATE_H