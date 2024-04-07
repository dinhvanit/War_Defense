#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "game_map.h"
#include "enemy.h"
#include <chrono>
#include <ctime>
#include "Timer.h"

class Game
{
    private:
        enum class TowerType{
            archer,
            canon,
            acy,
        }TypeCurrent;

    public:
        Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        ~Game(){};
//        void addTower(SDL_renderer* renderer, )

    private:
        int mouseStatus = 0;
        void draw(SDL_Renderer* renderer);
        void processEvents(SDL_Renderer* renderer, bool& is_quit);
        void addTower(SDL_Renderer* renderer);
        void addEnemy();
        void update(SDL_Renderer* renderer, float dT);
        void updateEnemy(float dT);

        vector<enemy> listEnemys;
//        vector<Tower> listTowers;

        Timer spawnTimer, roundTimer;
        int spawnEnemyCount;
};


#endif // GAME_H
