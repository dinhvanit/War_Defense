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
        enemy(SDL_Renderer* renderer, Block currentBlock, int currentLevel);
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

        void drawHealthBar(SDL_Renderer* renderer);

        EnemyState currentState;

//        void SetMaxHP(int currentLevel);

        int healthCurrent;

//ham lam cham quai
        void applySlowEffect(int effect);
//        void updateSlowEffect();//cap nhap hieu ung lam cham sau moi lan lap
        void resetSlowEffect();

    private:
        pos ePos;
        Block eBlock;
        static const float speed;
        int enemyW = 40;
        int enemyH = 50;
        int blockIndex;

        int healthMax = 100;

        float step;
//        int numFrames;
//        int CurrentFrame;
        SDL_Texture* enemyTexture;
        SDL_Texture* enemyTextureUp ;
        SDL_Texture* enemyTextureDown ;
        SDL_Texture* enemyTextureRight;

        SDL_Rect frame_clip[4];
        int numFrames;
        int CurrentFrame;

//hieu ung lam cham
        int slowEffect;//muc do lam cham

};

#endif // ENEMY_H
