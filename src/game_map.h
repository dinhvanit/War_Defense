#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 2
//cau truc du lieu luu trang thai tung o
 struct Block
{
    int x1, y1;
    int row, col;
    int isTowerIn;
    // bool isTowerIn = false;
};

class TileMat : public BaseObject
{
    public:
        TileMat();
        ~TileMat();
        bool isTowerIn;
    private:
        Block game_map_;

};

class GameMap
{
    public:
        GameMap();
        ~GameMap();
        void CreateMap();
        void LoadTiles(SDL_Renderer* renderer);
        //fill hinh anh vao cac vi tri
        void DrawMap(SDL_Renderer* renderer);

    private:
        Block game_map_;
        TileMat tile_[MAX_TILES];//luu dang hinh anh


};
int get_block_col(const int &x);
int get_block_row(const int &y);
#endif // GAME_MAP_H
