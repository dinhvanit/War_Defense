#include "enemy.h"

const float enemy::speed = 0.5f;
enemy::enemy() :
 numFrames(0), CurrentFrame(0), x_pos(X_UPPER_LEFT) ,y_pos(Y_UPPER_LEFT+TILE_HEIGHT*3), blockIndex(0), enemyTexture(nullptr)
 {
//    enemyTexture =loadTexture::loadT(renderer, "demon.png");
 }
enemy::~enemy()
{
    if(enemyTexture != nullptr){
        SDL_DestroyTexture(enemyTexture);
    }
}
void enemy::MakeParameter()
{
    int width =  380;
    int height = 296;
    for (int i=0;i<20;i++) {

        frame_clip[i].x = i * width;
        frame_clip[i].y = 0;
        frame_clip[i].w = width;
        frame_clip[i].h = height;
    }

    numFrames = 20;
}
void enemy::drawEnemy(SDL_Renderer* renderer, float x_pos, float y_pos)
{
    SDL_Rect eRect= {(int)( x_pos),(int) (y_pos), enemyW, enemyH }; // Vị trí và kích thước của
//    enemyTexture = loadTexture::loadT(renderer, "mage.png");
    SDL_RenderCopy(renderer, enemyTexture, &frame_clip[CurrentFrame], &eRect);
//    SDL_DestroyTexture(enemyTexture);
}
//moi lan vong lap game thi load anh tren map
//nen dung if khong can dung while

void enemy::moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath)
{
    enemyTexture = loadTexture::loadT(renderer, "1_run.png");
    int targetX = enemyPath[blockIndex].x1;
    int targetY = enemyPath[blockIndex].y1;
    cout << targetX <<" "<<targetY<<endl;
    if(x_pos < targetX)
    {
        x_pos+=5;
        cout << "dich phai"<<endl;
    }

    else if(x_pos > targetX) x_pos-=5;
    else if(y_pos < targetY) y_pos+=5;
    else if(y_pos > targetY) y_pos-=5;
    else
    {
        cout <<"tang chi so : " <<blockIndex<<endl;
        blockIndex = (blockIndex+1)% enemyPath.size();
    }
    drawEnemy(renderer, x_pos+TILE_WIDTH/4, y_pos+TILE_HEIGHT/4);
    CurrentFrame = (CurrentFrame + 1) % numFrames;
    SDL_RenderPresent(renderer);
    SDL_Delay(200);
}




//pos enemy::getPos(){
//    return pos;
//}
//
//bool enemy::isAlive(){
//    return (healthCurrent > 0);
//}
//
//void Unit::removeHealth(int damage) {
//	if (damage > 0) {
//		healthCurrent -= damage;
//		if (healthCurrent < 0)
//			healthCurrent = 0;
//	}
//}
