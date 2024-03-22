#include "CommonFunc.h"
#include "BaseObject.h"
#include "game_map.h"

int main(int argc, char* argv[]){
    if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
		cout << "Error: Couldn't initialize SDL Video = " << SDL_GetError() << endl;
		return 1;
	}
	else{
        SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            cout << "Error: Couldn't create window = " << SDL_GetError() << endl;
            return 1;
        }
        else{
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                    SDL_RENDERER_PRESENTVSYNC);
            if (renderer == nullptr) {
                cout << "Error: Couldn't create renderer = " << SDL_GetError() << endl;
                return 1;
            }
            else{
                //Output the name of the render driver.

    //            SDL_RendererInfo rendererInfo;
    //            SDL_GetRendererInfo(renderer, &rendererInfo);
    //            cout << "Renderer = " << rendererInfo.name << endl;

                Game game(window, renderer,SCREEN_WIDTH , SCREEN_HEIGHT);
                    SDL_DestroyRenderer(renderer);
                }
                SDL_DestroyWindow(window);
            }
        }
        SDL_Quit();
	}
    return 0;
}

