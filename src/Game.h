#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "game_map.h"
#include "enemy.h"
#include <chrono>
#include <ctime>
#include "Timer.h"
//#include "Tower.h"
#include <memory>
#include "BaseTower.h"
#include "Archer.h"
#include "Canon.h"
#include "Mage.h"


class Game
{
    private:
        enum class TowerType{
            archer,
            canon,
            mage,
        }TypeCurrent;

    public:
        Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool& GameTrue, bool& RestartGame);
        ~Game();
//        void addTower(SDL_renderer* renderer, )

    private:
        void draw(SDL_Renderer* renderer);
        void processEvents(SDL_Renderer* renderer, bool& is_quit, bool& GameTrue);

//        void addTower(SDL_Renderer* renderer, pos posM);
        //add thap
        void addArcherTower(SDL_Renderer* renderer, pos posM);
        void addCanonTower(SDL_Renderer* renderer, pos posM);
        void addMageTower(SDL_Renderer* renderer, pos posM);


        void addEnemy(SDL_Renderer* renderer, Block sBlock);

        void updates(SDL_Renderer* renderer, float dT);
        void updateEnemys(float dT);
        void updateTowers(SDL_Renderer* renderer, Map& gmap);
        void updateSpawnEnemy(SDL_Renderer* renderer, float dT);

        void DestroyTower(pos posM);

        void showText(SDL_Renderer* renderer, string input, int x, int y, int size, SDL_Color color);
        void showCurrentTower(SDL_Renderer* renderer);
        void showPauseMenu(SDL_Renderer* renderer, bool& GameTrue, bool& RestartGame);
        void showDefeatBoard(SDL_Renderer* renderer, bool& GameTrue, bool& RestartGame);

        Mix_Chunk* loadSound(string fileAudio);
        Mix_Music* loadMusic(string fileMusic);

        vector<shared_ptr<enemy>> listEnemys;
        //smart pointer shared_ptr weak_ptr
        vector<shared_ptr<BaseTower>> listTowers;
//        listTowers.push_back(new Cannon(fjal;fjlasjf))

        Timer spawnTimer, roundTimer, gameStartTimer;

        GameMap game_map;

        int spawnEnemyCount;//so quai 1 turn

        int currentGold=0;
        int HeartCURRENT;
        int currentLevel;

        SDL_Texture* defeatTexture=nullptr;

        bool defeat=false;
        bool is_quit = false;
        bool PauseMenu = false;

        bool Music;
        bool SoundFX;


        Mix_Chunk* Cowmoo=nullptr;
        Mix_Chunk* DefeatSound=nullptr;
        Mix_Music* musicGame=nullptr;
};


#endif // GAME_H
