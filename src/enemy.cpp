#include "enemy.h"

const float enemy::speed = 0.5f;
enemy::enemy(SDL_Renderer* renderer, Block currentBlock) :
 eBlock(start), step(2)
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
    if(eBlock.col==finish.col && eBlock.row==finish.row) healthCurrent = 0;
    runNextBlock();
}

void enemy::drawEnemy(SDL_Renderer* renderer)
{
    SDL_Rect eRect= {eBlock.x1+TILE_WIDTH/4, eBlock.y1+TILE_HEIGHT/4, enemyW, enemyH }; // Vị trí và kích thước của
    SDL_RenderCopy(renderer, enemyTexture, NULL, &eRect);
}
//moi lan vong lap game thi load anh tren map
//nen dung if khong can dung while



Block enemy::getBlock()
{
//    cout << eBlock.row <<" "<<eBlock.col;
    return eBlock;
}
Block enemy::getNextBlock()
{
    vector<Block> sPath = GameMap::findShortestPath(gmap, eBlock, finish);
    return sPath[1];
};


void enemy::runNextBlock()
{
//    Block tempCurrBlock = getBlock();


    Block tempNextBlock = getNextBlock();
    cout << tempNextBlock.x1 <<" "<<tempNextBlock.x2 <<endl;
    if( tempNextBlock.y1 > eBlock.y1)
	{
//		setState(stateWalkUp);
        cout <<"di len"<<endl;
        eBlock.y1 -= step;
	}
	else if(tempNextBlock.y1 < eBlock.y1)
	{
//		setState(stateWalkDown);
        cout <<"di xuong"<<endl;
        eBlock.y1 += step;
	}
	else if(tempNextBlock.x1 > eBlock.x1)
	{
		cout <<"di sang phai"<<endl;
        eBlock.x1 += step;
	}
	else if(tempNextBlock.x1 < eBlock.x1)
	{
//		setState(stateWalkLeft);
        cout <<"di sang trai"<<endl;
        eBlock.x1 -= step;
	}
	else {
        eBlock=getNextBlock();

	}
}


//
bool enemy::isAlive(){
    return (healthCurrent > 0);
}
//
//void enemy::getDamage(int damage) {
//	if (damage > 0) {
//		healthCurrent -= damage;
//		if (healthCurrent < 0)
//			healthCurrent = 0;
//	}
//}
