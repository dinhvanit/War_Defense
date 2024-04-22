#include "Canon.h"

const float Canon::weaponRange =140.0f;


Canon::Canon(SDL_Renderer* renderer, pos _pos):
    BaseTower(renderer, _pos), damage(1), targetEnemy(nullptr), cost(100)
{
    textureTower = loadTexture::loadT(renderer, "canon.png");
}
//
//Tower::~Tower()
//{
//    dtor
//}

void Canon::updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) {
    float closestDistance=weaponRange;
    float tamY=posM.first*TILE_HEIGHT+TILE_HEIGHT/2+Y_UPPER_LEFT;
    float tamX=posM.second*TILE_WIDTH+TILE_WIDTH+X_UPPER_LEFT;
    for (const auto& enemy : listEnemys) {
        float distanceSquared = (tamX - enemy->getBlock().x1) * (tamX - enemy->getBlock().x1) +
                                (tamY - enemy->getBlock().y1) * (tamY - enemy->getBlock().y1);                                (tamY - enemy->getBlock().y2) * (tamY - enemy->getBlock().y2);
        float distance = sqrt(distanceSquared);

//        cout << distance <<" khoang cach "<<endl;
        if (distance <= closestDistance) {
//            closestDistanceSquared = distanceSquared;
            closestDistance=distance;
            targetEnemy = enemy;
        }
    }
}

void Canon::attackEnemy() {
    if (targetEnemy != nullptr) {

        if (targetEnemy->isAlive()) {

            targetEnemy->getDamage(damage);

        } else {

            targetEnemy = nullptr;
        }
    }
}

void Canon::draw(SDL_Renderer* renderer){
    gmap[posM.first][posM.second]=Block(posM.first, posM.second, 1);
    SDL_Rect rect = {gmap[posM.first][posM.second].x1,gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
    SDL_RenderCopy(renderer, textureTower, NULL, &rect);

    float tamX = gmap[posM.first][posM.second].x2;
    float tamY = gmap[posM.first][posM.second].y2;
    float enemyX = targetEnemy->getBlock().x1+TILE_HEIGHT/2;
    float enemyY = targetEnemy->getBlock().y1+TILE_WIDTH/2;

    SDL_SetRenderDrawColor(renderer, 38, 0, 253, 0);
    SDL_RenderDrawLine(renderer, tamX, tamY, enemyX, enemyY);
}
int Canon::getCost()
{
    return cost;
}

bool Canon::CheckTowerInBlock(int row, int col)
{
    return ((int)posM.first==row && (int)posM.second == col);
}
