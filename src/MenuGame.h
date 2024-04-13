#ifndef MENUGAME_H
#define MENUGAME_H

#include "CommonFunc.h"
#include "loadTexture.h"

typedef enum{
    START,
    HOW_TO_PLAY,
    QUIT
}Selection;
class MenuGame
{
public:

    MenuGame(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    ~MenuGame();

    Selection ShowMenu();
    void RenderHowToPlay();
private:
    SDL_Event e;
//    const pos StartXY={0, 0};
//    const pos SizeSelection={0, 0};
//    const pos HowToPlayXY={0, 0};
//    const pos Quit={0, 0};
    const int SizeSelectionW = SCREEN_WIDTH/3;
    const int SizeSelectionH = 100;

    SDL_Window* window;
    SDL_Renderer* renderer;

    void cleanup();

};

#endif // MENUGAME_H
