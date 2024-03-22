#include "game_map.h"

void GameMap::CreateMap()
{
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            Block temp;
            temp.x1 = X_UPPER_LEFT + (x * BLOCK_WIDTH);
            temp.x2 = temp.x1 + BLOCK_WIDTH;
            temp.y1 = Y_UPPER_LEFT + (y * BLOCK_HEIGHT);
            temp.y2 = temp.y1 + BLOCK_HEIGHT;

            game_map_[y][x] = temp;
        }
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
    //Draw the tile's background color.
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            if ((x + y) % 2 == 0)

            else


            SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
            SDL_RenderFillRect(renderer, &rect);
        }
    }
    }

int get_block_col(const int &x)
{
    int res = (x - X_UPPER_LEFT) / BLOCK_WIDTH;
    if (!is_in(0, res, HORIZ_BLOCK_COUNT - 1))
        res = -1;
    return res;
}
int get_block_row(const int &y)
{
    int res = (y - Y_UPPER_LEFT) / BLOCK_HEIGHT;
    if (!is_in(0, res, VERT_BLOCK_COUNT - 1))
        res = -1;
    return res;
}
