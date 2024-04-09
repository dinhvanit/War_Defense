#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include "game_map.h"
#include <vector>
#include "time.h"
#include <memory>//share_ptr

//typedef enum{
//    stateNone = 0;̬
//    stateWalkRight,
//    stateWalkLeft,
//	stateWalkUp,
//	stateWalkDown,
//	stateDeath,
//	stateFrozen
//}EnemyState;
//typedef enum{
//    DEMON = 0;
//    ORC,
//    WOLF,
//}EnemyName;

class enemy
{
    public:
        enemy(SDL_Renderer* renderer, Block currentBlock);
//        ~enemy();

        void updateEnemy(SDL_Renderer* renderer, vector <shared_ptr<enemy>>& listEnemys);

        void drawEnemy(SDL_Renderer* renderer);
//        void moveInBlock();
        void moveInMap(SDL_Renderer* renderer);

        Block getNextBlock();

        Block getBlock();

        void getDamage(int damage);

        bool isAlive();

        void runNextBlock();

    private:
        pos ePos;
        Block eBlock;
        static const float speed;
        int enemyW = 40;
        int enemyH = 50;
        int blockIndex;
        const int healthMax = 10;
        int healthCurrent = healthMax;
        float step;
//        int numFrames;
//        int CurrentFrame;
        SDL_Texture* enemyTexture ;
};

#endif // ENEMY_H
