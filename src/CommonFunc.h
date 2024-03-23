#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <iostream>
#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <unordered_map>

using namespace std;


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;

//screen
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "War Defense";
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR = 0xff;
//tile
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 100;
//tao map 11*7 o
const int nCOL = 11;
const int nROW = 7;
//bang de thanh chon defense
const int X_UPPER_LEFT=200;
const int Y_UPPER_LEFT=0;
//
struct Block
{
    int x1, y1, x2, y2;
    int row, col;
    int isTowerIn[nROW][nCOL];
    // bool isTowerIn = false;
    char* file_name_;
};

#endif // COMMONFUNC_H
