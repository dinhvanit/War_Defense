#include "Game.h"


Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT):
    TypeCurrent(TowerType::archer),
    spawnTimer(0.5f), roundTimer(5.0f), currentGold(GoldStart), defeat(false), defeatTexture(loadTexture::loadT(renderer, "defeat.png")),
    currentLevel(0), spawnEnemyCount(0), gameStartTimer(20.0f)
{
    if (window != nullptr && renderer != nullptr) {
        bool is_quit = false;

        auto time1 = std::chrono::system_clock::now();
        auto time2 = std::chrono::system_clock::now();

        const float dT = 1.0f / 60.0f;
//        SDL_Rect rectbar = {0, 0, X_UPPER_LEFT, SCREEN_HEIGHT};
//        SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "StatusBar.png"), NULL, &rectbar);
//        SDL_RenderPresent(renderer);
        while(!is_quit){

            time2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();
            //load hoat anh
            if(timeDeltaFloat >= dT){
                time1=time2;
                processEvents(renderer, is_quit);
                updates(renderer, dT);
//                cout <<"vang hien tai la "<<currentGold<<endl;
//                cout <<"so mang hien tai la ==="<<HeartCURRENT<<endl;
                if(HeartCURRENT<0){
                    SDL_Rect defeatRect = {(SCREEN_WIDTH-X_UPPER_LEFT)/4+X_UPPER_LEFT, (SCREEN_HEIGHT-Y_UPPER_LEFT)/3,(SCREEN_WIDTH-X_UPPER_LEFT)/2, (SCREEN_HEIGHT-Y_UPPER_LEFT)/3};
                    SDL_RenderCopy(renderer, defeatTexture, NULL, &defeatRect);
                    SDL_RenderPresent(renderer);
                }
                else{
                    draw(renderer);
                }

            }
        }
    }
}
//Game::~Game()
//{
//    //dtor
//}



void Game::processEvents(SDL_Renderer* renderer, bool& is_quit)
{
    bool mouseDownThisFrame = false;
//    while(!is_quit){
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                is_quit = true;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    //Quit the game.
                case SDL_SCANCODE_ESCAPE:
                    is_quit = true;
                    break;
                case SDL_SCANCODE_1:
                    TypeCurrent = TowerType :: archer;
                    cout << "chon type archer"<<endl;
                    break;
                case SDL_SCANCODE_2:
                    TypeCurrent = TowerType :: canon;
                    cout << "chon type canon"<<endl;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                mouseDownThisFrame = (mouseStatus == 0);
                if (event.button.button == SDL_BUTTON_LEFT){
                    mouseStatus = SDL_BUTTON_LEFT;
                    cout << SDL_BUTTON_LEFT <<endl;
                }
                else if (event.button.button == SDL_BUTTON_RIGHT){
                    mouseStatus = SDL_BUTTON_RIGHT;
                    cout << SDL_BUTTON_RIGHT <<endl;

                }
            break;
            case SDL_MOUSEBUTTONUP:
                mouseStatus = 0;
                break;
            }
        }
    int mouseX =0;
    int mouseY=0;
    SDL_GetMouseState(&mouseX, &mouseY);
    pos posM = GameMap::getBlockInMap(mouseX, mouseY);

    if(mouseStatus > 0)
    {
        switch (mouseStatus)
        {
            case SDL_BUTTON_LEFT:
                if( gmap[posM.first][posM.second].isTowerIn == 0 && currentGold>=priceTower ){
                    gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
                    if(!GameMap::ConDuong(gmap)) {
                        cout << "khong dat duoc vi tri nay!"<<endl;
                        gmap[posM.first][posM.second]=Block(posM.first, posM.second, 0);
                    }
                    else {
                        currentGold-=priceTower;
                        SDL_Rect rect = {gmap[posM.first][posM.second].x1,gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
                        switch (TypeCurrent) {
                        case TowerType::archer:
                            addTower(renderer, posM);
            //                cout << "ve ra archer o vi tri "<<posM.first << " "<<posM.second<<"====="<<endl;
//                                SDL_RenderCopy(renderer,loadTexture::loadT(renderer, "Archer.png"), NULL, &rect);
                            break;
                        case TowerType::canon:
            //                cout << "ve ra canon o vi tri "<<posM.first << " "<<posM.second<<"====="<<endl;
                                SDL_RenderCopy(renderer,loadTexture::loadT(renderer, "canon.png"), NULL, &rect);
                            break;
                        }
                    }
                }
                break;
            case SDL_BUTTON_RIGHT:
                DestroyTower(posM);
//                cout <<"ao vai chuong"<<endl;
                break;
        }
    }
}
//    }//bo vong lap game ra khoi xu ly su kien
//    cout << "khong truy cap vao duoc"<<endl;





void Game::updates(SDL_Renderer* renderer, float dT)
{
    updateEnemys(dT);

    for(auto& towerSelected : listTowers){
        towerSelected.updateTarget(renderer, dT, listEnemys);
        towerSelected.attackEnemy();
    }

    updateSpawnEnemy(renderer, dT);

}
//cap nhap dinh vi quai
void Game::updateEnemys(float dT)
{
    auto it = listEnemys.begin();
    while (it != listEnemys.end()) {
        bool increment = true;

        if ((*it) != nullptr) {
            (*it)->updateEnemy(renderer, listEnemys, gmap, HeartCURRENT);
            if ((*it)->isAlive() == false) {
                currentGold+=goldEnemy;
                it = listEnemys.erase(it);
                increment = false;
            }
        }

        if (increment)
            it++;
    }
}



void Game::updateSpawnEnemy(SDL_Renderer* renderer, float dT)
{
    gameStartTimer.countDown(dT);
    if(gameStartTimer.timeSIsZero()){
        spawnTimer.countDown(dT);
        //bat dau moi round moi
        if(listEnemys.empty() && spawnEnemyCount == 0){
            roundTimer.countDown(dT);
            if (roundTimer.timeSIsZero()){
                spawnEnemyCount = countEnemy;
                currentLevel++;
                roundTimer.resetToMax();
            }
        }
    }
    //them quai vao round
    if(spawnEnemyCount > 0 && spawnTimer.timeSIsZero()){
        addEnemy(renderer, start);
        spawnEnemyCount--;
        spawnTimer.resetToMax();
    }
}

void Game::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    game_map.DrawMap(renderer);
    for(auto& enemySelected : listEnemys)
        if(enemySelected != nullptr)
            enemySelected->drawEnemy(renderer);


    for(auto& towerSelected : listTowers)
        towerSelected.draw(renderer);
    showText(renderer, to_string(currentGold), 100, 550+Y_UPPER_LEFT, TEXT_SIZE );
    showText(renderer, to_string(HeartCURRENT), 100, 610+Y_UPPER_LEFT, TEXT_SIZE);
    showText(renderer, to_string(currentLevel), 300, 50, TEXT_SIZE);
    SDL_RenderPresent(renderer);
}




//void Game::addEnemy(SDL_Renderer* renderer)
void Game::addTower(SDL_Renderer* renderer, pos posM)
{
    listTowers.push_back(Tower(renderer, posM));
}



void Game::addEnemy(SDL_Renderer* renderer, Block sBlock){
    listEnemys.push_back(make_shared<enemy>(renderer, sBlock));
}


void Game::showText(SDL_Renderer* renderer,string input, int x, int y,int size)
{
    if(TTF_Init()==-1){
        cout <<"loi "<<endl;
    }
    TTF_Font* font = TTF_OpenFont("assets/textfonts/VNI-Hobo.TTF", size);
        if (font == nullptr) {
            cout<< "Failed to load font: " << TTF_GetError() << endl;
    }

    SDL_Color White = {255,255,255};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, input.c_str(), White);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
}
void Game::DestroyTower(pos posM) {
    for (auto it = listTowers.begin(); it != listTowers.end();) {
        if ((*it).CheckTowerInBlock(posM.first, posM.second)){
            it = listTowers.erase(it);
            gmap[posM.first][posM.second].isTowerIn=0;
        }
        else
            it++;
    }
}


