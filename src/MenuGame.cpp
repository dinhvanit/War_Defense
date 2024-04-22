#include "MenuGame.h"

MenuGame::MenuGame(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
    : window(window), renderer(renderer)
    {}

MenuGame::~MenuGame() {}

Selection MenuGame::ShowMenu() {
    bool isMenu = true;
    SDL_Event e;
    Selection choice = START;

    while (isMenu) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);

            // Ve nen menu chinh
            SDL_Rect backgroundRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "TowerDefenseBackGround.png"), NULL, &backgroundRect);

            // Ve lua chon Start
            SDL_Rect startRect = {SCREEN_WIDTH/3, SCREEN_HEIGHT/3, SizeSelectionW, SizeSelectionH};
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "StartButton.png"), NULL, &startRect);

            // Ve lua chon How to play
            SDL_Rect howToPlayRect = {SCREEN_WIDTH/3, SCREEN_HEIGHT/3+120, SizeSelectionW, SizeSelectionH};
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "howtoplaybutton.png"), NULL, &howToPlayRect);
            //Ve lua chon Quit
            SDL_Rect quitRect = {SCREEN_WIDTH/3, SCREEN_HEIGHT/3+120*2, SizeSelectionW, SizeSelectionH};
            SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "quitbutton.png"), NULL, &quitRect);

            SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                choice = QUIT;
                isMenu = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p ={x, y};
                if (SDL_PointInRect(&p, &startRect)){
                    // chon Start
                    choice = START;
                    isMenu = false;
                }
                else if (SDL_PointInRect(&p, &howToPlayRect)) {
                    // chon How to play
                    choice = HOW_TO_PLAY;
                    RenderHowToPlay();
                }
                else if (SDL_PointInRect(&p, &quitRect)){
                    choice = QUIT;
                    isMenu = false;
                }
            }
        }
    }
    return choice;
}

void MenuGame::RenderHowToPlay() {
    bool isRunning = true;
    SDL_Event e;

    while (isRunning) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // ve nen how to play, va phim back lai menu
        SDL_Rect howToPlayRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "howtoplay.png"), NULL, &howToPlayRect);

        SDL_Rect backRect = {howToPlayRect.w-BUTTON_SIZE, 0, BUTTON_SIZE, BUTTON_SIZE};
        SDL_RenderCopy(renderer, loadTexture::loadT(renderer, "backbutton.png"), NULL, &backRect);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                SDL_Point p ={x, y};
                if (SDL_PointInRect(&p, &backRect)) {
                    // nguoi choi back tro lai menu, thoat vong lap cua so how to play
                    isRunning = false;
                }
            }
//            cout <<"dang trong cua so how to play"<<endl;
        }
    }
}
