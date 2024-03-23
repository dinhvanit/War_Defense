#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    if (window != nullptr && renderer != nullptr) {
        bool is_quit = false;
        while(!is_quit){
            processEvents(renderer, is_quit);
            draw(renderer);
        }
    }
}
//Game::~Game()
//{
//    //dtor
//}
void Game::processEvents(SDL_Renderer* renderer, bool& is_quit)
{
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
            }
        }
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
