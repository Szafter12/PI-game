#ifndef GAME_PI_COLLIDER_H
#define GAME_PI_COLLIDER_H

class Enemy;
class Player;

class Collider {
    public:
        static void calculatePosition(Enemy &enemy1, Enemy &enemy2, float dt);
        static void calculatePosition(Player &player, Enemy &enemy, float dt);
};


#endif //GAME_PI_COLLIDER_H