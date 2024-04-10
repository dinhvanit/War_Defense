#ifndef TOWER_H
#define TOWER_H

#include "CommonFunc.h"
#include "enemy.h"
#include "Timer.h"
#include <memory>
#include <cmath>

class Tower
{

    public:
        Tower(SDL_Renderer* renderer, pos _pos);
        void update(SDL_Renderer* renderer, float dT);
//        void addTower(SDL_Renderer* renderer,Map& gmap, int x, int y);
        void draw(SDL_Renderer* renderer);
        void attackEnemy();
        void updateTarget(SDL_Renderer* renderer,float dT, vector<shared_ptr<enemy>>& listEnemys);
        int getCost();

    private:
        bool updateA(float dT);
        pos posM;
        shared_ptr<enemy> targetEnemy;
        static const float weaponRange;//vung tan cong
        SDL_Texture* textureTower = nullptr;
        int damage;
        int cost;
};

#endif // TOWER_H
