#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"
#include "loadTexture.h"

#define MAX_TILES 2
//cau truc du lieu luu trang thai tung o


class TileMat : public BaseObject
{
    public:
        TileMat(){;}
        ~TileMat(){;}
};

class GameMap
{
    public:
        GameMap(){};
        ~GameMap(){};
        //tao map luu chi so;
        void CreateMap();
        void LoadTiles(SDL_Renderer* _renderer);
        //fill hinh anh vao cac vi tri
        void DrawMap(SDL_Renderer* _renderer);

    private:
        Block game_map_;
        TileMat tile_[MAX_TILES];//luu dang hinh anh
};
#endif // GAME_MAP_H
