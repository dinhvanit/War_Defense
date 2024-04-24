#include "Game.h"


Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool& GameTrue):
    TypeCurrent(TowerType::archer),
    spawnTimer(1.0f), roundTimer(5.0f), HeartCURRENT(HeartStart), currentGold(GoldStart), defeat(false), defeatTexture(loadTexture::loadT(renderer, "defeat.png")),
    currentLevel(0), spawnEnemyCount(0), gameStartTimer(5.0f, 5.0f)
{
    if (window != nullptr && renderer != nullptr) {
//        bool is_quit = false;

        auto time1 = std::chrono::system_clock::now();
        auto time2 = std::chrono::system_clock::now();

        const float dT = 1.0f / 60.0f;

        while(!is_quit){

            time2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();
            //load hoat anh
            if(timeDeltaFloat >= dT){
                time1=time2;
//                cout <<"vang hien tai la "<<currentGold<<endl;
//                cout <<"so mang hien tai la ==="<<HeartCURRENT<<endl;
                if(HeartCURRENT>0 ) defeat=false;
                else defeat=true;
                if(!defeat){
                    if(!PauseMenu){
                        processEvents(renderer, is_quit, GameTrue);
                        updates(renderer, dT);
                        draw(renderer);
                    }
                    else
                    {
                        showPauseMenu(renderer, GameTrue);
                    }
                }
                else {
                    showDefeatBoard(renderer, GameTrue);
                }
            }
        }
    }
}
Game::~Game()
{
    loadTexture::deallocateTextures();
}

void Game::processEvents(SDL_Renderer* renderer, bool& is_quit, bool& GameTrue)
{
    bool mouseDownThisFrame = false;
    SDL_Rect PauseButtonRect ={SCREEN_WIDTH-100*1, 10, BUTTON_SIZE, BUTTON_SIZE};
//    while(!is_quit){

    int mouseX =0;
    int mouseY=0;
    pos posM;
    SDL_GetMouseState(&mouseX, &mouseY);
    SDL_Point pM={mouseX, mouseY};
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                is_quit = true;
                GameTrue = false;
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
                case SDL_SCANCODE_3:
                    TypeCurrent = TowerType :: mage;
                    cout <<"chon type mage"<<endl;
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                posM = GameMap::getBlockInMap(mouseX, mouseY);
                cout <<"bam chuot xuong"<<endl;
                if(mouseX>X_UPPER_LEFT && mouseY>Y_UPPER_LEFT){
                    cout <<"chuot ben trong"<<endl;
                    if(event.button.button == SDL_BUTTON_LEFT){
                        cout <<"bam chuot trai"<<endl;
                        if( gmap[posM.first][posM.second].isTowerIn == 0 && currentGold>=priceTower ){
                            gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
                            if(!GameMap::ConDuong(gmap)) {
                                cout << "khong dat duoc vi tri nay!"<<endl;
                                gmap[posM.first][posM.second]=Block(posM.first, posM.second, 0);
                            }
                            else{
                                SDL_Rect rect = {gmap[posM.first][posM.second].x1,gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
                                switch (TypeCurrent) {
                                case TowerType::archer:
                                    if(currentGold>=priceArcher) {
                                        addArcherTower(renderer, posM);
                                        currentGold-=priceArcher;
                                    }
                                    else {
                                        gmap[posM.first][posM.second]=Block(posM.first, posM.second, 0);
                                        cout << "khong du tien dat archer" <<endl;
                                    }
                                    break;
                                case TowerType::canon:
                                    if(currentGold>=priceCanon){
//                                        cout <<"add canon"<<endl;
                                        addCanonTower(renderer, posM);
                                        currentGold-=priceCanon;
                                    }
                                    else {
                                        gmap[posM.first][posM.second]=Block(posM.first, posM.second, 0);
                                        cout << "khong du tien dat canon" <<endl;
                                    }
                                    break;
                                }
                            }
                        }
                    }
                    else if (event.button.button == SDL_BUTTON_RIGHT){
                            DestroyTower(posM);
                    }
                }
                else {
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if (SDL_PointInRect(&pM, &PauseButtonRect)){
                            PauseMenu=true;
                            cout <<"bam pause"<<endl;
                        }
                    }
                }
            }
        }
}





void Game::updates(SDL_Renderer* renderer, float dT)
{
    updateEnemys(dT);

    for(auto& towerSelected : listTowers){
        towerSelected->updateTarget(renderer, dT, listEnemys);
        towerSelected->attackEnemy();
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
//                for (auto& enemy : listEnemys) {
//                    enemy->SetMaxHP(currentLevel);
//                }
                currentLevel++;
                roundTimer.resetToMax();
            }
        }
    }
    //them quai vao round
    if(spawnEnemyCount > 0 && spawnTimer.timeSIsZero()){
//        for (auto& enemy : listEnemys) {
//            enemy->SetMaxHP(currentLevel);
//            cout <<enemy->healthCurrent<<"la hp con hien tai"<<endl;
//        }
        cout <<"quai dot = " <<currentLevel<<endl;
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
        towerSelected->draw(renderer);
    showText(renderer, to_string(currentGold), 100, 550+Y_UPPER_LEFT, TEXT_SIZE , Yellow);
    showText(renderer, to_string(HeartCURRENT), 100, 610+Y_UPPER_LEFT, TEXT_SIZE, Red);
    showText(renderer, to_string(currentLevel), 300, 50, TEXT_SIZE, White);

    showCurrentTower(renderer);

    SDL_RenderPresent(renderer);
}




//void Game::addEnemy(SDL_Renderer* renderer)
//void Game::addTower(SDL_Renderer* renderer, pos posM)
//{
//    listTowers.push_back(Tower(renderer, posM));
//
//}

// add các loại tháp
void Game::addArcherTower(SDL_Renderer* renderer, pos posM) {
    shared_ptr<Archer> archerPtr = make_shared<Archer>(renderer, posM);
    listTowers.push_back(archerPtr);
}
void Game::addCanonTower(SDL_Renderer* renderer, pos posM) {
    shared_ptr<Canon> canonPtr = make_shared<Canon>(renderer, posM);
    listTowers.push_back(canonPtr);
}
//void Game::addCanonTower(SDL_Renderer* renderer, pos posM) {
//    listTowers.push_back(Canon(renderer, posM));
//}
//
//void Game::addMageTower(SDL_Renderer* renderer, pos posM) {
//    listTowers.push_back(Mage(renderer, posM));
//}




void Game::addEnemy(SDL_Renderer* renderer, Block sBlock){
    listEnemys.push_back(make_shared<enemy>(renderer, sBlock, currentLevel));
}



void Game::showText(SDL_Renderer* renderer,string input, int x, int y,int size, SDL_Color color)
{
    if(TTF_Init()==-1){
        cout <<"loi "<<endl;
    }
    TTF_Font* font = TTF_OpenFont("assets/textfonts/VNI-Hobo.TTF", size);
        if (font == nullptr) {
            cout<< "Failed to load font: " << TTF_GetError() << endl;
    }
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, input.c_str(), color);
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
//    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = {x, y, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
}
void Game::DestroyTower(pos posM)
{
    for (auto it = listTowers.begin(); it != listTowers.end();) {
        if ((*it)->CheckTowerInBlock(posM.first, posM.second)){
            currentGold+=(*it)->getCost()/2;
            it = listTowers.erase(it);

//            currentGold+=priceTower/2;//hoan lai 50% gold

            gmap[posM.first][posM.second].isTowerIn=0;
        }
        else
            it++;
    }

}

void Game::showCurrentTower(SDL_Renderer* renderer ){
    SDL_Rect CurTowerRect ={SCREEN_WIDTH-100*4-30, 10, BUTTON_SIZE, BUTTON_SIZE};
    switch (TypeCurrent)
    {
        case TowerType::archer:
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "archer.png"), NULL, &CurTowerRect);
            break;
        case TowerType::canon:
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "canon.png"), NULL, &CurTowerRect);
            break;
        case TowerType::mage:
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "mage.png"), NULL, &CurTowerRect);
            break;
    }
}

void Game::showPauseMenu(SDL_Renderer* renderer, bool& GameTrue){
    SDL_Rect PauMenuRect = {X_UPPER_LEFT+4*TILE_WIDTH, Y_UPPER_LEFT + TILE_WIDTH, 4*TILE_WIDTH, 5*TILE_HEIGHT};
    SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "menu.png"), NULL, &PauMenuRect);
    SDL_RenderPresent(renderer);
    SDL_Rect BackToGameRect = {562, 585, 242, 75};
    SDL_Rect MainMenu = {609, 532, 150, 35};
    SDL_Rect ResetLevel = {609, 479, 150, 35};
//    SDL_Rect MainMenu = {0, 0, 300, 300};
//    SDL_Rect Music = {609, 333, 60, 14};
//    SDL_Rect SoundFX = {575, 363, 85, 14};
    SDL_Event eMenu;
    while(PauseMenu)
    {
        while(SDL_PollEvent(&eMenu)){
//            if(eMenu.type = SDL_QUIT){
//                PauseMenu=false;
//            }
            if(eMenu.type == SDL_QUIT){
                PauseMenu=false;
                is_quit = true;
                GameTrue = false;
                break;
            }
            else if (eMenu.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p ={x, y};
                cout << x <<" " <<y<<endl;
                if (SDL_PointInRect(&p, &MainMenu)) {
                    PauseMenu=false;
                    is_quit=true;
//                    cout <<"vao main menu"<<endl;
                }

                else if (SDL_PointInRect(&p, &BackToGameRect)){
                    PauseMenu=false;
                }
            }

        }
    }
}
void Game::showDefeatBoard(SDL_Renderer* renderer, bool& GameTrue)
{
    SDL_Rect DefeatBoardRect = {X_UPPER_LEFT+4*TILE_WIDTH, Y_UPPER_LEFT + TILE_WIDTH, 4*TILE_WIDTH, 5*TILE_HEIGHT};
    SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "defeatBoard.png"), NULL, &DefeatBoardRect);
    showText(renderer, to_string(currentLevel), 650, 350, 72, Red);
    SDL_RenderPresent(renderer);

    SDL_Rect MainMenu = {567, 592, 100, 43};
    SDL_Rect ResetLevel = {694, 592, 100, 43};

    SDL_Event eDefeat;

    while(SDL_PollEvent(&eDefeat)){
        if(eDefeat.type == SDL_QUIT){
                is_quit = true;
                GameTrue = false;
                break;
        }
        else if (eDefeat.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            SDL_Point p ={x, y};
            cout << x <<" " <<y<<endl;
            if (SDL_PointInRect(&p, &MainMenu)) {
                is_quit=true;
                break;
            }
        }
    }
}
