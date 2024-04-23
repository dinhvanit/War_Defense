#ifndef BASETOWER_H
#define BASETOWER_H

#include "CommonFunc.h"
#include "enemy.h"
#include "Timer.h"
#include <memory>
#include <cmath>

class BaseTower {
public:
    BaseTower(SDL_Renderer* renderer, pos _pos);

    virtual void updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) = 0;
    virtual void attackEnemy() = 0;
    virtual void draw(SDL_Renderer* renderer) = 0;
    virtual int getCost() = 0;
    virtual bool CheckTowerInBlock(int row, int col) = 0;
    virtual bool isOutOfRange(shared_ptr<enemy> enemy) = 0;

protected:
    pos posM;
    shared_ptr<enemy> targetEnemy;
    SDL_Texture* textureTower;
    int damage, cost;
};

#endif // BASETOWER_H
