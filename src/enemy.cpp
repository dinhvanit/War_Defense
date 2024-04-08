#include "enemy.h"

const float enemy::speed = 0.5f;
enemy::enemy(SDL_renderer* renderer, Block currentBlock) :
 numFrames(0), CurrentFrame(0), eBlock(0, 3, 3)
 {
    enemyTexture =loadTexture::loadT(renderer, "demon.png");
 }


//enemy::~enemy()
//{
//    if(enemyTexture != nullptr){
//        SDL_DestroyTexture(enemyTexture);
//    }
//}

void enemy::updateEnemy(SDL_Renderer* renderer, vector <shared_ptr<enemy>>& listEnemys)
{

}

void enemy::drawEnemy(SDL_Renderer* renderer, Block curBlock)
{
    SDL_Rect eRect= {curBlock.x1+TILE_WIDTH/4, curBlock.y1+TILE_HEIGHT/4, enemyW, enemyH }; // Vị trí và kích thước của
    SDL_RenderCopy(renderer, enemyTexture, NULL, &eRect);
}
//moi lan vong lap game thi load anh tren map
//nen dung if khong can dung while

//void enemy::moveInMap(SDL_Renderer* renderer, vector<Block> enemyPath)
//{
//    enemyTexture = loadTexture::loadT(renderer, "1_run.png");
//    int targetX = enemyPath[blockIndex].x1;
//    int targetY = enemyPath[blockIndex].y1;
//    cout << targetX <<" "<<targetY<<endl;
//    if(x_pos < targetX)
//    {
//        x_pos+=5;
//        cout << "dich phai"<<endl;
//    }
//
//    else if(x_pos > targetX) x_pos-=5;
//    else if(y_pos < targetY) y_pos+=5;
//    else if(y_pos > targetY) y_pos-=5;
//    else
//    {
//        cout <<"tang chi so : " <<blockIndex<<endl;
//        blockIndex = (blockIndex+1)% enemyPath.size();
//    }
//    drawEnemy(renderer, x_pos+TILE_WIDTH/4, y_pos+TILE_HEIGHT/4);
//    SDL_Delay(200);
//}




Block enemy::getBlock()
{
    cout << eBlock.row <<" "<<eBlock.col;
    return eBlock;
}
Block enemy::getNextBlock()
{
    vector<Block> sPath = GameMap::findShortestPath(gmap, eBlock, finish);
    return sPath[1];
}


void enemy::runNextBlock()
{

}

//
//bool enemy::isAlive(){
//    return (healthCurrent > 0);
//}
//
//void enemy::getDamage(int damage) {
//	if (damage > 0) {
//		healthCurrent -= damage;
//		if (healthCurrent < 0)
//			healthCurrent = 0;
//	}
//}
