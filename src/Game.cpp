#include "Game.h"


Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT):
    TypeCurrent(TowerType::archer),
    spawnTimer(0.25f), roundTimer(5.0f)

{
    if (window != nullptr && renderer != nullptr) {
        bool is_quit = false;

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
                processEvents(renderer, is_quit);
                updates(renderer, dT);
//                for (int i = 0; i < nROW; ++i) {
//                        for (int j = 0; j < nCOL; ++j) {
//                            cout << gmap[i][j].isTowerIn << "\t";
//                        }
//                        cout <<endl;
//                }
                draw(renderer);

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
                if( gmap[posM.first][posM.second].isTowerIn == 0 ){
                    gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
                    if(!GameMap::ConDuong(gmap)) {
                        cout << "khong dat duoc vi tri nay!"<<endl;
                        gmap[posM.first][posM.second]=Block(posM.first, posM.second, 0);
                    }
                    else {
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
//                        SDL_RenderPresent(renderer);
                    }
                }

            break;
        }
    }
//    }//bo vong lap game ra khoi xu ly su kien
//    cout << "khong truy cap vao duoc"<<endl;
}




void Game::updates(SDL_Renderer* renderer, float dT)
{
    updateEnemys(dT);

    updateSpawnEnemy(renderer, dT);
}
//cap nhap quai
void Game::updateEnemys(float dT)
{
    auto it = listEnemys.begin();
    while (it != listEnemys.end()) {
        bool increment = true;

        if ((*it) != nullptr) {
            (*it)->updateEnemy(renderer, listEnemys, gmap);
            if ((*it)->isAlive() == false) {
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
    spawnTimer.countDown(dT);
    //bat dau moi round moi
    if(listEnemys.empty() && spawnEnemyCount == 0){
        roundTimer.countDown(dT);
        if (roundTimer.timeSIsZero()){
            spawnEnemyCount = countEnemy;
            roundTimer.resetToMax();
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





