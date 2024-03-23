#include "game_map.h"

void GameMap::CreateMap()
{
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            game_map_.isTowerIn[y][x]=1;
        }
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
    SDL_Texture* tile1 = loadTexture::loadT(renderer, "Frontyard1.jpg");
    SDL_Texture* tile2 = loadTexture::loadT(renderer, "Frontyard2.jpg");
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            if ((x + y) % 2 == 0){
                SDL_Rect rect = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                SDL_RenderCopy(renderer, tile1, NULL, &rect);
            }
            else{
                SDL_Rect rect = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                SDL_RenderCopy(renderer, tile2, NULL, &rect);
            }
        }
    }
}
