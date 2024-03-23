#include "game_map.h"

void GameMap::CreateMap()
{
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            game_map_.isTowerIn[y][x]=0;
        }
    }
}

void GameMap::DrawMap(SDL_Renderer* renderer)
{
    SDL_Texture* tile1 = loadTexture::loadT(renderer, "Frontyard1.jpg");
    SDL_Texture* tile2 = loadTexture::loadT(renderer, "Frontyard2.jpg");
    SDL_Texture* tile3 = loadTexture::loadT(renderer, "Start.jpg");
    SDL_Texture* tile4 = loadTexture::loadT(renderer, "Finish.jpg");
    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            SDL_Rect rect = { x * TILE_WIDTH+X_UPPER_LEFT, y * TILE_HEIGHT+Y_UPPER_LEFT, TILE_WIDTH, TILE_HEIGHT };
            if(x==0 && y ==nROW/2) SDL_RenderCopy(renderer, tile3, NULL, &rect);
            else if(x==nCOL-1 && y==nROW/2) SDL_RenderCopy(renderer, tile4, NULL, &rect);
            else{
                if ((x + y) % 2 == 0){
                SDL_RenderCopy(renderer, tile1, NULL, &rect);
            }
                else{
                SDL_RenderCopy(renderer, tile2, NULL, &rect);
                }
            }
        }
    }
}
