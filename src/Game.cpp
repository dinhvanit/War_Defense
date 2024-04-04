#include "Game.h"
#include "game_map.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)

{
    if (window != nullptr && renderer != nullptr) {
        bool is_quit = false;
        draw(renderer);
        while(!is_quit){
//            draw(renderer);

//            Block start = gmap[nROW / 2][0]; // Lấy start từ CreateMap()
//            Block finish = gmap[nROW / 2][nCOL - 1]; // Lấy finish từ CreateMap()
//            vector<Block> shortestPath = GameMap::findShortestPath(gmap, start, finish);
//            enemy enm;
//            enm.moveInMap(renderer, shortestPath);
            processEvents(renderer, is_quit);

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
            //                cout << "ve ra archer o vi tri "<<posM.first << " "<<posM.second<<"====="<<endl;
                                SDL_RenderCopy(renderer,loadTexture::loadT(renderer, "Archer.png"), NULL, &rect);
                            break;
                        case TowerType::canon:
            //                cout << "ve ra canon o vi tri "<<posM.first << " "<<posM.second<<"====="<<endl;
                                SDL_RenderCopy(renderer,loadTexture::loadT(renderer, "canon.png"), NULL, &rect);
                            break;
                        }
                        SDL_RenderPresent(renderer);
                    }
                }

            break;
        }
    }
//    }//bo vong lap game ra khoi xu ly su kien
//    cout << "khong truy cap vao duoc"<<endl;
}

void Game::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    GameMap game_map;
    game_map.DrawMap(renderer);
    SDL_RenderPresent(renderer);
}
//void Game::addEnemy(SDL_Renderer* renderer)
