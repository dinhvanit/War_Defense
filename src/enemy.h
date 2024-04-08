#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include "game_map.h"
#include <vector>
#include "time.h"

class enemy
{
    public:
        enemy();
        ~enemy();
        enemy(SDL_Renderer* renderer, int x, int y);
        void drawEnemy(SDL_Renderer* renderer, float x_pos, float y_pos);
//        void moveInBlock();
        void moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath);
        pos getPos();
        void removeHealth(int damege);
        bool isAlive();
        SDL_Texture* enemyTexture ;
        void MakeParameter();
    private:
        int x_pos;
        int y_pos;
        int w;
        int h;
        static const float speed;
        int enemyW = 40;
        int enemyH = 50;
        int blockIndex;
        const int healthMax = 10;
        int healthCurrent = healthMax;
        int numFrames;
        int CurrentFrame;
        SDL_Rect frame_clip[20];
};

#endif // ENEMY_H
