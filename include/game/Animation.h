#ifndef GAME_PI_ANIMATION_H
#define GAME_PI_ANIMATION_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

class Animation {
public:
    int frameCount;
    int frame=0;
    int posX;
    int posY;
    int frameW;
    int frameH;
    float speed;
    sf::Sprite *sprite;
    sf::Clock time;
    bool pause=false;

public:
    Animation(sf::Sprite *sprite, int frame_count, int pos_x, int pos_y, int frame_w, int frame_h, float speed)
        : sprite(sprite),
          frameCount(frame_count),
          posX(pos_x),
          posY(pos_y),
          frameW(frame_w),
          frameH(frame_h),
          speed(speed) { sprite->setTextureRect(sf::IntRect({posX,posY},{frameW,frameH}));
    }

    void update() {
        if (frameCount>1) {
            if (!pause) {
                if (!time.isRunning()) time.start();
                if(time.getElapsedTime().asSeconds()>=speed) {
                    time.restart();
                    sprite->setTextureRect(sf::IntRect({posX+(frameW*frame),posY},
                        {frameW,frameH}));
                    frame++;
                    if (frame==frameCount) frame=0;
                }
            }
        }
        else sprite->setTextureRect(sf::IntRect({posX,posY},{frameW,frameH}));
    }
    void set(sf::Vector2i position) {
        sprite->setTextureRect(sf::IntRect({position.x,position.y},{frameW,frameH}));
    }

};

#endif //GAME_PI_ANIMATION_H