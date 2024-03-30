#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include "game_map.h"
#include <vector>

class enemy
{
    public:
        enemy();
        ~enemy();
        enemy(SDL_Renderer* renderer, int x, int y);
        void drawEnemy(SDL_Renderer* renderer, float x_pos, float y_pos);
//        void moveInBlock();
        void moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath);

    private:
        int x_pos;
        int y_pos;
        int w;
        int h;
        int enemyW = 40;
        int enemyH = 40;
        SDL_Texture* enemyTexture = nullptr;
        int blockIndex;
};

#endif // ENEMY_H
