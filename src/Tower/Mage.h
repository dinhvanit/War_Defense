#ifndef MAGE_H
#define MAGE_H

#include "BaseTower.h"

class Mage : public BaseTower
{
public:
    Mage(SDL_Renderer* renderer, pos _pos);

    void updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) override;
    void attackEnemy() override;
    void draw(SDL_Renderer* renderer) override;
    int getCost() override;
    bool CheckTowerInBlock(int row, int col) override;
    bool isOutOfRange(shared_ptr<enemy> enemy) override;
private:
    vector<std::shared_ptr<enemy>> targetEnemies;
    shared_ptr<enemy> targetEnemy;
    static const float weaponRange;
    SDL_Texture* textureTower = nullptr;
    int damage;
    int slowEffect;
    int slowDuration;
    int cost;
};

#endif // MAGE_H
