#include "enemy.h"

enemy::enemy() : x_pos(0+TILE_WIDTH/2) ,y_pos(TILE_WIDTH*3/2), blockIndex(0)
{
    enemyTexture = loadTexture::loadT(renderer, "zombie.png");
}
//    enemyTexture = loadTexture::loadT(renderer, "zombie.png");

//
enemy::~enemy()
{
    SDL_DestroyTexture(enemyTexture);
}

void enemy::drawEnemy(SDL_Renderer* renderer, float x_pos, float y_pos)
{
    SDL_Rect eRect= {(int)( x_pos),(int) (y_pos), enemyW, enemyH }; // Vị trí và kích thước của animation
    SDL_RenderCopy(renderer, enemyTexture, NULL, &eRect);

    SDL_DestroyTexture(enemyTexture);
}

void enemy::moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath)
{
    float distancePerFrame = 120.0/(float) FPS; //4 don vi khung hinh/s

    float targetX = enemyPath[blockIndex].x1+TILE_WIDTH/2;
    float targetY = enemyPath[blockIndex].y1+TILE_HEIGHT/2;
    if ( x_pos <targetX || y_pos > targetY )
    {   if( x_pos<targetX) x_pos=x_pos+distancePerFrame;
        if(y_pos>targetY) y_pos=y_pos-distancePerFrame;

    }
    else
        {
            blockIndex = blockIndex +1 ;
        }
        drawEnemy(renderer, x_pos, y_pos);
     SDL_Delay(1000/FPS);
}
