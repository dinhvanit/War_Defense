#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "game_map.h"
#include "enemy.h"
#include <chrono>
#include <ctime>
#include "Timer.h"
#include "Tower.h"
#include <memory>

class Game
{
    private:
        enum class TowerType{
            archer,
            canon,
            mage,
        }TypeCurrent;

    public:
        Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
        ~Game(){};
//        void addTower(SDL_renderer* renderer, )

    private:
        void draw(SDL_Renderer* renderer);
        void processEvents(SDL_Renderer* renderer, bool& is_quit);

        void addTower(SDL_Renderer* renderer, pos posM);
        void addEnemy(SDL_Renderer* renderer, Block sBlock);

        void updates(SDL_Renderer* renderer, float dT);
        void updateEnemys(float dT);
        void updateTowers(SDL_Renderer* renderer, Map& gmap);
        void updateSpawnEnemy(SDL_Renderer* renderer, float dT);

        void DestroyTower(pos posM);

        void showText(SDL_Renderer* renderer, string input, int x, int y, int size);

//        void DestroyTower(SDL_renderer* renderer, Block posM);

        int mouseStatus = 0;

        vector<shared_ptr<enemy>> listEnemys;
        //smart pointer shared_ptr weak_ptr
        vector<Tower> listTowers;

        Timer spawnTimer, roundTimer, gameStartTimer;

        GameMap game_map;

        int spawnEnemyCount;//so quai 1 turn

        int currentGold=0;

        bool defeat;

        SDL_Texture* defeatTexture=nullptr;
        int currentLevel;
};


#endif // GAME_H
