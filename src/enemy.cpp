#include "enemy.h"

enemy::enemy() : x_pos(0) ,y_pos(660.0)
{
    enemyTexture = loadTexture::loadT(renderer, "zombie.png");
}
//    enemyTexture = loadTexture::loadT(renderer, "zombie.png");

//
enemy::~enemy()
{
    SDL_DestroyTexture(enemyTexture);
}
//void enemy::drawEnemy(SDL_Renderer* renderer,float x_pos,float y_pos) {
//    SDL_Rect Rect = {(int)( x_pos),(int) (y_pos), 50, 50 }; // Vị trí và kích thước của animation
//    SDL_RenderCopy(renderer, texture, NULL, &Rect);
//}
//enemy::draw(SDL_Renderer* renderer)
//{
//    if (renderer != nullptr) {
//		//Draw the image at the unit's position.
//		int w, h;
//		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
//		SDL_Rect rect = ()
//		SDL_RenderCopy(renderer, enemyTexture, NULL, &rect);
//	}
//}
