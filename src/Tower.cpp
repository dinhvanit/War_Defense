#include "Tower.h"

const float Tower::weaponRange = 5.0f;


Tower::Tower(SDL_Renderer* renderer, pos _pos):
    posM (_pos), damage(10), targetEnemy(nullptr)
{
    textureTower = loadTexture::loadT(renderer, "archer.png");
}
//
//Tower::~Tower()
//{
//    dtor
//}

void Tower::updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) {
    float closestDistanceSquared = weaponRange * weaponRange; // Bình phương của khoảng cách tối đa

    for (const auto& enemy : listEnemys) {
        float distanceSquared = (posM.first - enemy->getBlock().x1) * (posM.first - enemy->getBlock().x1) +
                                (posM.second - enemy->getBlock().y1) * (posM.second - enemy->getBlock().y1);
        if (distanceSquared <= closestDistanceSquared) {
            closestDistanceSquared = distanceSquared;
            targetEnemy = enemy;
        }
    }
}

void Tower::attackEnemy() {
    if (targetEnemy != nullptr) {
        // Kiểm tra xem quái vật vẫn còn sống
        if (targetEnemy->isAlive()) {
            // Bắn quái vật (thực hiện hành động bắn)
            targetEnemy->getDamage(damage);
        } else {
            // Nếu quái vật đã chết hoặc không còn nằm trong phạm vi bắn, đặt targetEnemy = nullptr để tìm mục tiêu mới
            targetEnemy = nullptr;
        }
    }
}

void Tower::draw(SDL_Renderer* renderer){
    gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
    SDL_Rect rect = {gmap[posM.first][posM.second].x1,gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
    SDL_RenderCopy(renderer, textureTower, NULL, &rect);
}
