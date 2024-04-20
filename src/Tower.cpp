#include "Tower.h"

const float Tower::weaponRange =190.0f;


Tower::Tower(SDL_Renderer* renderer, pos _pos):
    posM (_pos), damage(1), cost(50)
{
    textureTower = loadTexture::loadT(renderer, "archer.png");
}
//
//Tower::~Tower()
//{
//    dtor
//}
void Tower::updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) {

    if (targetEnemy.expired() || (!targetEnemy.expired() && (!targetEnemy.lock()->isAlive() || isOutOfRange(targetEnemy.lock())))) {
        float closestDistance = weaponRange;
        float tamY = gmap[posM.first][posM.second].y2;
        float tamX = gmap[posM.first][posM.second].x2;

        weak_ptr<enemy> closestEnemy;

        for (const auto& enemy : listEnemys) {
            float distanceSquared = (tamX - enemy->getBlock().x2) * (tamX - enemy->getBlock().x2) +
                                    (tamY - enemy->getBlock().y2) * (tamY - enemy->getBlock().y2);
            float distance = sqrt(distanceSquared);
            if (distance <= closestDistance) {
                closestDistance = distance;
                closestEnemy = enemy;
            }
        }

        if (auto lockedEnemy = closestEnemy.lock()) {
            targetEnemy = closestEnemy;
        }
    }
}

bool Tower::isOutOfRange(shared_ptr<enemy> enemy) {

    float tamY = gmap[posM.first][posM.second].y2;
    float tamX = gmap[posM.first][posM.second].x2;
    float enemyX = enemy->getBlock().x2;
    float enemyY = enemy->getBlock().y2;
    float distanceSquared = (tamX - enemyX) * (tamX - enemyX) + (tamY - enemyY) * (tamY - enemyY);
    float distance = sqrt(distanceSquared);
    return distance > weaponRange;
}

void Tower::attackEnemy() {
    if (auto lockedEnemy = targetEnemy.lock()) {
        if (lockedEnemy->isAlive()) {
            lockedEnemy->getDamage(damage);
//            cout <<"kill enemy ========" <<endl;
        } else {
            targetEnemy.reset();
        }
    }
}

void Tower::draw(SDL_Renderer* renderer){
    gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
    SDL_Rect rect = {gmap[posM.first][posM.second].x1,gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
    SDL_RenderCopy(renderer, textureTower, NULL, &rect);

    if (auto lockedEnemy = targetEnemy.lock()) {
        // Nếu có, vẽ đường chỉ từ tháp đến con quái
        float tamX = gmap[posM.first][posM.second].x2;
        float tamY = gmap[posM.first][posM.second].y2;
        float enemyX = lockedEnemy->getBlock().x1+TILE_HEIGHT/2;
        float enemyY = lockedEnemy->getBlock().y1+TILE_WIDTH/2;

        SDL_SetRenderDrawColor(renderer, 255, 41, 41, 0);
        SDL_RenderDrawLine(renderer, tamX, tamY, enemyX, enemyY);
    }
}
int Tower::getCost()
{
    return cost;
}

bool Tower::CheckTowerInBlock(int row, int col)
{
    return ((int)posM.first==row && (int)posM.second == col);
}

