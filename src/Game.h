#ifndef GAME_H
#define GAME_H

#include "CommonFunc.h"
#include "game_map.h"
#include "enemy.h"


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
        void addEnemy();
//        void addTower(SDL_renderer* renderer, )

    private:
        int mouseStatus = 0;
        void draw(SDL_Renderer* renderer);
        void processEvents(SDL_Renderer* renderer, bool& is_quit);
};

#endif // GAME_H
