#include "Game.h"
#include "game_map.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    if (window != nullptr && renderer != nullptr) {
        bool is_quit = false;
        while(!is_quit){
            draw(renderer);
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
    GameMap gm;
    bool mouseDownThisFrame = false;
    while(!is_quit){
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
                }
            case SDL_MOUSEBUTTONDOWN:
                mouseDownThisFrame = (mouseStatus == 0);
                if (event.button.button == SDL_BUTTON_LEFT){
                    mouseStatus = SDL_BUTTON_LEFT;
                    int mouseX = 0, mouseY = 0;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    cout << mouseX << " "<<mouseY<<endl;
                    int y = (mouseY-Y_UPPER_LEFT)/TILE_HEIGHT;
                    int x = (mouseX-X_UPPER_LEFT)/TILE_WIDTH;
                    cout << y <<" "<<x <<" "<< gmap[y][x].isTowerIn<<endl;
                    if( gmap[y][x].isTowerIn == 0){

                        SDL_Rect rect = {(mouseX-X_UPPER_LEFT)/TILE_WIDTH*TILE_WIDTH+X_UPPER_LEFT, (mouseY-Y_UPPER_LEFT)/TILE_HEIGHT*TILE_HEIGHT+Y_UPPER_LEFT, TILE_WIDTH, TILE_HEIGHT };
                        SDL_RenderCopy(renderer,loadTexture::loadT(renderer, "Archer.png"), NULL, &rect);
                        SDL_RenderPresent(renderer);
                        gmap[y][x]=Block(y, x, 1);
                    }
                    vector<Block> shortestPath = GameMap::findShortestPath(gmap, gmap[3][0], gmap[3][12]);
                    for (const auto& block : shortestPath) {
                        cout << "(" << block.row << ", " << block.col << ")" << endl;
                    }
                    cout << "trang thai hien tai la"<<endl;
                    for (int i = 0; i < nROW; ++i) {
                        for (int j = 0; j < nCOL; ++j) {
                            cout << gmap[i][j].isTowerIn << " ";
                        }
                        cout << endl;
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    mouseStatus = SDL_BUTTON_RIGHT;
                break;
            case SDL_MOUSEBUTTONUP:
                mouseStatus = 0;
                break;

            }
        }
//        int mouseX = 0, mouseY = 0;
//        SDL_GetMouseState(&mouseX, &mouseY);
//        if(mouseStatus > 0)
//        {
//            cout << mouseX << " "<<mouseY<<endl;
//            SDL_Texture* Archer = loadTexture::loadT(renderer, "archer.png");
//            SDL_Rect rect = { mouseX, mouseY, TILE_WIDTH, TILE_HEIGHT };
//            SDL_RenderCopy(renderer,Archer, NULL, &rect);
//        }

    }

}
void Game::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    GameMap game_map;
    game_map.DrawMap(renderer);
    SDL_RenderPresent(renderer);
}
