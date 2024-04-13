#include "CommonFunc.h"
#include "game_map.h"
#include "Game.h"
#include "MenuGame.h"

bool InitData()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
		cout << "Error: Couldn't initialize SDL Video = " << SDL_GetError() << endl;
		return false;
	}
	else{
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(),SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            cout << "Error: Couldn't create window = " << SDL_GetError() << endl;
            success = false;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) {
                cout << "Error: Couldn't create renderer = " << SDL_GetError() << endl;
                success = false;
            }
            else{
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags)){
                    cout << "Error: Couldn't init flags = " << SDL_GetError() << endl;
                    success = false;
                }
            }
        }
	}
	return true;
}
void close()
{
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}
int main(int argc, char* argv[]){
    if(InitData() == false)
        return 1;
    // Tạo đối tượng MenuGame
    MenuGame menu(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Hiển thị menu và lấy lựa chọn từ người chơi
    Selection choice = menu.ShowMenu();

    // Kiểm tra lựa chọn và thực hiện các hành động tương ứng
    if (choice == START) {
        // Người chơi đã chọn Start, bắt đầu trò chơi
        Game game(window, renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }
//    else if (choice == HOW_TO_PLAY) {
//        // Người chơi đã chọn How to play, hiển thị hướng dẫn chơi
//        menu.RenderHowToPlay();
//        cout << "truy cap vao vi tri"<<endl;
//    }
    close();
    return 0;
}

