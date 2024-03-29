#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include <vector>

class enemy
{
    public:
        enemy();
        ~enemy();
        enemy(SDL_Renderer* renderer, int x, int y);
        void drawEnemy(SDL_Renderer* renderer, float x_pos, float y_pos);
//        void moveInBlock();
//        void moveInMap();

    private:
        int x_pos;
        int y_pos;
        int w;
        int h;

        SDL_Texture* enemyTexture = nullptr;
};

#endif // ENEMY_H
