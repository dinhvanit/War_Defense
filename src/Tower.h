#ifndef TOWER_H
#define TOWER_H

#include "CommonFunc.h"
#include "enemy.h"
#include "Timer.h"


class Tower
{

    public:
        Tower(SDL_Renderer* renderer, pos _pos);
        void update(SDL_Renderer* renderer, float dT);
//        void addTower(SDL_Renderer* renderer,Map& gmap, int x, int y);
        void draw(SDL_Renderer* renderer);
        void attack(Map gmap);

    private:
        bool updateA(float dT);
        pos posM;
        static const float weaponRange;//vung tan cong
        SDL_Texture* textureTower = nullptr;
};

#endif // TOWER_H
