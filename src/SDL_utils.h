#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include "CommonFunc.h"


void logSDLError(ostream& os, const string &msg, bool fatal = false);

void initSDL(SDL_Window* &g_window, SDL_Renderer* &g_screen,const int SCREEN_WIDTH,const int SCREEN_HEIGHT,const string &WINDOW_TITLE);

void quitSDL(SDL_Window* g_window, SDL_Renderer* g_screen);

void waitUntilKeyPressed();


#endif // SDL_UTILS_H
