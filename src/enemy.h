#ifndef ENEMY_H
#define ENEMY_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include "game_map.h"
#include <vector>
#include "time.h"
#include <memory>//share_ptr

typedef enum{
    stateWalkRight,
    stateWalkLeft,
	stateWalkUp,
	stateWalkDown,
	stateGetDamage,
	stateDeath,
//	stateFrozen
}EnemyState;
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

        void updateEnemy(SDL_Renderer* renderer, vector <shared_ptr<enemy>>& listEnemys, Map gmap, int& CurrentHeart);

        void drawEnemy(SDL_Renderer* renderer);
//        void moveInBlock();
        void moveInMap(SDL_Renderer* renderer);

        Block getNextBlock(Map gmap);

        Block getBlock();

        void getDamage(int damage);

        bool isAlive();

        void runNextBlock(Map gmap);

        void MakeAnimation();

        EnemyState currentState;

        void SetMaxHP(int currentLevel);

    private:
        pos ePos;
        Block eBlock;
        static const float speed;
        int enemyW = 40;
        int enemyH = 50;
        int blockIndex;
        int healthMax = 50;
        int healthCurrent;
        float step;
//        int numFrames;
//        int CurrentFrame;
        SDL_Texture* enemyTexture;
        SDL_Texture* enemyTextureUp ;
        SDL_Texture* enemyTextureDown ;
        SDL_Texture* enemyTextureRight;

        SDL_Rect frameUp_clip[4];
        SDL_Rect frameDown_clip[4];
        SDL_Rect frameRight_clip[4];
        int numFrames;
        int CurrentFrame;


};

#endif // ENEMY_H
