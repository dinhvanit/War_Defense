#include "game_map.h"


void GameMap::DrawMap(SDL_Renderer* renderer)
{
    Map mp = CreateMap();
//    for (int y = 0; y < nROW; y++) {
//        for (int x = 0; x < nCOL; x++) {
//            cout <<"("<< mp[y][x].x1<<","<<mp[y][x].y1<<") "<<mp[y][x].isTowerIn<<endl;
//        }
//    }
    SDL_Texture* tile1 = loadTexture::loadT(renderer, "Frontyard1.jpg");
    SDL_Texture* tile2 = loadTexture::loadT(renderer, "Frontyard2.jpg");
    SDL_Texture* tileStart = loadTexture::loadT(renderer, "Start.jpg");
    SDL_Texture* tileFinish = loadTexture::loadT(renderer, "Finish.jpg");
    SDL_Texture* TowerBar = loadTexture::loadT(renderer, "TowerBar.png");
    SDL_Texture* Archer = loadTexture::loadT(renderer, "archer.png");
    SDL_Texture* Canon = loadTexture::loadT(renderer, "canon.png");
    SDL_Texture* Mage = loadTexture::loadT(renderer, "mage.png");
    //draw TowerBar selection
    SDL_Rect rectbar = {0, 0, X_UPPER_LEFT, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, TowerBar, NULL, &rectbar);

    SDL_Rect rectArcher = {10, 10, 180, 150};
    SDL_RenderCopy(renderer, Archer, NULL, &rectArcher);

    SDL_Rect rectCanon = {10, 180, 180, 150};
    SDL_RenderCopy(renderer, Canon, NULL, &rectCanon);

    SDL_Rect rectMage = {10,340, 180, 150};
    SDL_RenderCopy(renderer, Mage, NULL, &rectMage);

    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            SDL_Rect rect = { x * TILE_WIDTH+X_UPPER_LEFT, y * TILE_HEIGHT+Y_UPPER_LEFT, TILE_WIDTH, TILE_HEIGHT };
            if(x==0 && y ==nROW/2) SDL_RenderCopy(renderer, tileStart, NULL, &rect);
            else if(x==nCOL-1 && y==nROW/2) SDL_RenderCopy(renderer, tileFinish, NULL, &rect);
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

