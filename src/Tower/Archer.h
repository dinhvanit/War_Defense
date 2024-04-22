#ifndef ARCHER_H
#define ARCHER_H

#include "BaseTower.h"

class Archer : public BaseTower {
public:
    Archer(SDL_Renderer* renderer, pos _pos);

    void updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) override;
    void attackEnemy() override;
    void draw(SDL_Renderer* renderer) override;
    int getCost() override;
    bool CheckTowerInBlock(int row, int col) override;
    bool isOutOfRange(shared_ptr<enemy> enemy) override;
private:
    weak_ptr<enemy> targetEnemy;//target 1 con gần nhât
    static const float weaponRange;//vung tan cong
    SDL_Texture* textureTower = nullptr;
    int damage;
    int cost;
};

#endif // ARCHER_H
