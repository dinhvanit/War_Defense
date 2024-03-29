#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "loadTexture.h"
#include <queue>
#include <vector>
#include <algorithm>

class GameMap
{
    public:
        GameMap(){};
        ~GameMap(){};
        //tao map luu chi so;
        void LoadTiles(SDL_Renderer* _renderer);
        //fill hinh anh vao cac vi tri
        void DrawMap(SDL_Renderer* _renderer);
        static bool isValid(int col, int row, int rows, int cols);
        static vector<Block> findShortestPath(Map gmap, Block start, Block finish);

    private:
        SDL_Texture* tile1 = nullptr;
        SDL_Texture* tile2 = nullptr;
        SDL_Texture* tileStart = nullptr;
        SDL_Texture* tileFinish = nullptr;
        SDL_Texture* TowerBar = nullptr;
        SDL_Texture* Archer = nullptr;
        SDL_Texture* Canon = nullptr;
        SDL_Texture* Mage = nullptr;
};
Map CreateMap();
#endif // GAME_MAP_H
