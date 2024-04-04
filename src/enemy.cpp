#include "enemy.h"

enemy::enemy() : x_pos(X_UPPER_LEFT+TILE_WIDTH/4) ,y_pos(Y_UPPER_LEFT+TILE_HEIGHT*3+TILE_HEIGHT/4), blockIndex(0)
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
    SDL_Rect eRect= {(int)( x_pos),(int) (y_pos), enemyW, enemyH }; // Vị trí và kích thước của
    SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "zombie.png"), NULL, &eRect);
}
//moi lan vong lap game thi load anh tren map
//nen dung if khong can dung while
void enemy::moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath)
{
    int targetX = enemyPath[blockIndex].x1;
    int targetY = enemyPath[blockIndex].y1;
    if(enemyPath[blockIndex].x1 < targetX)
    {
        x_pos+=5;
    }
    else if(enemyPath[blockIndex].x1 < targetX) x_pos-=5;
    else if(enemyPath[blockIndex].x1 < targetX) y_pos+=5;
    else if(enemyPath[blockIndex].x1 < targetX) y_pos-=5;
    else
    {
        blockIndex++;
    }
    drawEnemy(renderer, x_pos+TILE_WIDTH/4, y_pos+TILE_HEIGHT/4);

    SDL_Delay(1000/FPS);
}
