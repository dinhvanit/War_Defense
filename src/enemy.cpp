#include "enemy.h"

const float enemy::speed = 0.5f;
enemy::enemy(SDL_Renderer* renderer, Block currentBlock) :
 eBlock(start), step(2), currentState(stateWalkRight), CurrentFrame(0), numFrames(4)
 {
    enemyTexture =loadTexture::loadT(renderer, "demon.png");
    enemyTextureUp = loadTexture::loadT(renderer, "botren.png");
    enemyTextureDown = loadTexture::loadT(renderer, "boxuong.png");
    enemyTextureRight = loadTexture::loadT(renderer, "bophai.png");
 }


//enemy::~enemy()
//{
//    if(enemyTexture != nullptr){
//        SDL_DestroyTexture(enemyTexture);
//    }
//}

void enemy::MakeAnimation()
{
    frameUp_clip[0]={0, 0, 141, 141};
    frameUp_clip[1]={141, 0, 141, 141};
    frameUp_clip[2]={282, 0, 141, 141};
    frameUp_clip[3]={423, 0, 141, 141};

//    frameDown_clip[0]={0, 0, 141, 141};
//    frameDown_clip[0]={141, 0, 141, 141};
//    frameDown_clip[0]={282, 0, 141, 141};
//    frameDown_clip[0]={423, 0, 141, 141};
//
//    frameRight_clip[0]={0, 0, 141, 141};
//    frameRight_clip[0]={141, 0, 141, 141};
//    frameRight_clip[0]={282, 0, 141, 141};
//    frameRight_clip[0]={423, 0, 141, 141};
}

void enemy::updateEnemy(SDL_Renderer* renderer, vector <shared_ptr<enemy>>& listEnemys, Map gmap)
{
    if(eBlock.col==finish.col && eBlock.row==finish.row) healthCurrent = 0;
    runNextBlock(gmap);
}

void enemy::drawEnemy(SDL_Renderer* renderer)
{
    MakeAnimation();
    SDL_Rect eRect= {eBlock.x1+TILE_WIDTH/4, eBlock.y1+TILE_HEIGHT/4, enemyW, enemyH }; // Vị trí và kích thước của
//    SDL_RenderCopy(renderer, enemyTexture, NULL, &eRect);
    CurrentFrame = (CurrentFrame + 1) % numFrames;
    switch(currentState)
    {
        case(stateWalkRight):
			SDL_RenderCopy(renderer, enemyTextureRight, &frameUp_clip[CurrentFrame/4], &eRect);
//			cout <<"bo phai"<<endl;
			break;
		case(stateWalkLeft):
            SDL_RenderCopyEx(renderer, enemyTextureRight, &frameUp_clip[CurrentFrame/4], &eRect, NULL, NULL, SDL_FLIP_HORIZONTAL);
			break;
		case(stateWalkUp):
            SDL_RenderCopy(renderer, enemyTextureUp, &frameUp_clip[CurrentFrame/4], &eRect);
			break;
		case(stateWalkDown):
            SDL_RenderCopy(renderer, enemyTextureDown, &frameUp_clip[CurrentFrame/4], &eRect);
			break;

    }
}
//moi lan vong lap game thi load anh tren map
//nen dung if khong can dung while



Block enemy::getBlock()
{
//    cout << eBlock.row <<" "<<eBlock.col;
    return eBlock;
}
Block enemy::getNextBlock(Map gmap)
{
    vector<Block> sPath = GameMap::findShortestPath(gmap, eBlock, finish);
//    cout <<"chuyen Block ======== " <<eBlock.row <<" "<<eBlock.col<<endl;
//    for(Block x : sPath) cout <<x.row <<","<<x.col << endl;
    return sPath[1];
};


void enemy::runNextBlock(Map gmap)
{
//    Block tempCurrBlock = getBlock();


    Block tempNextBlock = getNextBlock(gmap);
//    cout <<"vi tri ke tiep "<<tempNextBlock.x1 <<"==="<<tempNextBlock.y1<<endl;
//    cout <<eBlock.x1 <<" "<<eBlock.y1<<endl;
////    cout <<"vi tri Block hien tai ---- " << eBlock.x1 <<" "<<eBlock.y1 <<endl;
////    cout <<"vt tiep theo "<< tempNextBlock.x1 <<" "<<tempNextBlock.y1 <<endl;
////    for (int i = 0; i < nROW; ++i) {
////        for (int j = 0; j < nCOL; ++j) {
////            cout << gmap[i][j].isTowerIn << "\t";
////        }
////        cout <<endl;
////    }
    if( tempNextBlock.y1 > eBlock.y1)
	{
//        cout <<"di xuong"<<endl;
//        cout <<tempNextBlock.y1 <<"    "<<eBlock.y1<<"     ======"<<endl;
        eBlock.y1 += step;
        currentState=stateWalkDown;
	}
	else if(tempNextBlock.y1 < eBlock.y1)
	{
//		setState(stateWalkUp);
//        cout <<"di len"<<endl;
        eBlock.y1 -= step;
        currentState=stateWalkUp;
	}
	else if(tempNextBlock.x1 > eBlock.x1)
	{
//		cout <<"di sang phai"<<endl;
        eBlock.x1 += step;
        currentState=stateWalkRight;
	}
	else if(tempNextBlock.x1 < eBlock.x1)
	{
//		setState(stateWalkLeft);
//        cout <<"di sang trai"<<endl;
        eBlock.x1 -= step;
        currentState=stateWalkLeft;
	}
	else {
        eBlock=getNextBlock(gmap);
//        cout <<"chuyen Block ======== " <<eBlock.row <<" "<<eBlock.col<<endl;
//        cout <<eBlock.x1 <<" ===== " <<eBlock.x2<<endl;
	}
}

//
bool enemy::isAlive(){
    return (healthCurrent > 0);
}
//
void enemy::getDamage(int damage) {
	if (damage > 0) {
		healthCurrent -= damage;
		if (healthCurrent < 0)
			healthCurrent = 0;
	}
}
