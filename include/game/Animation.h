#ifndef GAME_PI_ANIMATION_H
#define GAME_PI_ANIMATION_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"

class Animation {
    int frameCount;
    int frame=0;
    int posX;
    int posY;
    int frameW;
    int frameH;
    int speed;
    sf::Sprite *sprite;
    sf::Clock time;

public:
    Animation(sf::Sprite *sprite, int frame_count, int pos_x, int pos_y, int frame_w, int frame_h, int speed)
        : sprite(sprite),
          frameCount(frame_count),
          posX(pos_x),
          posY(pos_y),
          frameW(frame_w),
          frameH(frame_h),
          speed(speed) { sprite->setTextureRect(sf::IntRect({posX,posY},{frameW,frameH}));
    }

    void play() {
        if (frameCount>1) {
            if (!time.isRunning()) time.start();
            if(time.getElapsedTime().asSeconds()>=speed) {
                time.restart();
                frame++;
                sprite->setTextureRect(sf::IntRect({posX+(frameW*frame),posY+(frameH*frame)},
                    {frameW,frameH}));
                if (frame>=frameCount-1) frame=0;
            }
        }
    }


};

#endif //GAME_PI_ANIMATION_H