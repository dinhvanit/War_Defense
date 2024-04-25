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
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;


static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;
static SDL_Event event;
//static TTF_Font* gFont = NULL;

//screen
const int SCREEN_WIDTH = 1240;
const int SCREEN_HEIGHT = 800;
const string WINDOW_TITLE = "War Defense";
const int SCREEN_BPP = 32;
const int FPS = 60;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B =180;

const int RENDER_DRAW_COLOR = 0xff;
//tile
const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 100;
//bang de thanh chon defense
const int X_UPPER_LEFT=200;
const int Y_UPPER_LEFT=100;

//tao map nCOL*nROW 13*7
const int nCOL = (SCREEN_WIDTH - X_UPPER_LEFT)/TILE_WIDTH ;
const int nROW = (SCREEN_HEIGHT - Y_UPPER_LEFT)/TILE_HEIGHT ;
//
struct Block {
    int x1, y1, x2, y2;
    int row, col;
    int isTowerIn;

    // Khai báo hàm tạo mặc định
    Block() {}

    // Hàm tạo với đầy đủ tham số
    Block(int _row, int _col, int _isTowerIn) {
        this->row = _row;
        this->col = _col;
        this->isTowerIn = _isTowerIn;

        // Tính toán giá trị của các thành viên dựa trên các tham số truyền vào
        this->x1 = this->col * TILE_WIDTH + X_UPPER_LEFT;
        this->y1 = this->row * TILE_HEIGHT + Y_UPPER_LEFT;
        this->x2 = this->x1 + TILE_WIDTH/2;
        this->y2 = this->y1 + TILE_HEIGHT/2;
    }
};
typedef vector<vector<Block>> Map;
typedef pair<int, int> pos;
Map CreateMap();
static Map gmap = CreateMap();

const Block start = Block(nROW/2, 0 , 3);
const Block finish = Block(nROW/2, nCOL-1, 4);

//so quai moi turn
const int countEnemy = 5;

//const int STATE_UP = 0;

//vang khoi tao

const int GoldStart = 100;
const int priceTower = 50;
const int goldEnemy = 15;

const int HeartStart = 10;

const int TEXT_SIZE = 30;

const int BUTTON_SIZE = 80;

// bang gia thap

const int priceArcher = 50;
const int priceCanon = 100;
const int priceMage = 75;


const SDL_Color Black = {0, 0, 0};
const SDL_Color White = {255, 255, 255};
const SDL_Color Yellow = {255, 255, 0};
const SDL_Color Red = {255, 0, 0};

#endif // COMMONFUNC_H
