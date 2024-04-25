#include "Mage.h"

const float Mage::weaponRange = 150.0f;

Mage::Mage(SDL_Renderer* renderer, pos _pos) :
    BaseTower(renderer, _pos), damage(0), cost(priceMage), slowEffect(2), slowDuration(10)
{
    textureTower = loadTexture::loadT(renderer, "mage.png");
    targetEnemies = vector<shared_ptr<enemy>>();
}

void Mage::updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) {

    targetEnemies.clear();

    float tamY = gmap[posM.first][posM.second].y2;
    float tamX = gmap[posM.first][posM.second].x2;

    for (const auto& enemy : listEnemys) {
        if (enemy != nullptr && enemy->isAlive()) {
            float distanceSquared = (tamX - enemy->getBlock().x2) * (tamX - enemy->getBlock().x2) +
                                    (tamY - enemy->getBlock().y2) * (tamY - enemy->getBlock().y2);
            float distance = sqrt(distanceSquared);
            if (distance <= weaponRange) {
                targetEnemies.push_back(enemy);
                enemy->applySlowEffect(2);
            }
            else {
                enemy->resetSlowEffect();
            }
        }
    }
}

void Mage::draw(SDL_Renderer* renderer) {
    if (textureTower != nullptr) {
        gmap[posM.first][posM.second] = Block(posM.first, posM.second, 1);
        SDL_Rect rect = { gmap[posM.first][posM.second].x1, gmap[posM.first][posM.second].y1, TILE_WIDTH, TILE_HEIGHT };
        SDL_RenderCopy(renderer, textureTower, NULL, &rect);

        float tamX = gmap[posM.first][posM.second].x2;
        float tamY = gmap[posM.first][posM.second].y2;

        for (const auto& targetEnemy : targetEnemies) {
            if (targetEnemy != nullptr && targetEnemy->isAlive()) {
                float enemyX = targetEnemy->getBlock().x1 + TILE_HEIGHT / 2;
                float enemyY = targetEnemy->getBlock().y1 + TILE_WIDTH / 2;

                SDL_SetRenderDrawColor(renderer, 38, 0, 253, 0);
                SDL_RenderDrawLine(renderer, tamX, tamY, enemyX, enemyY);
            }
        }
    }
}


void Mage::attackEnemy() {
    for (auto& enemy : targetEnemies) {
        if (enemy != nullptr && enemy->isAlive()) {
            enemy->getDamage(damage);
        }
    }

//    for (auto it = targetEnemies.begin(); it != targetEnemies.end();)
//    {
//        if (!(*it)->isAlive()) {
//            it = targetEnemies.erase(it);
//        }
//        else
//        {
//            ++it;
//        }
//    }

    targetEnemies.erase(
        std::remove_if(
            targetEnemies.begin(), targetEnemies.end(),
            [](const std::shared_ptr<enemy>& e) {
                return !e->isAlive();
            }),
        targetEnemies.end()
    );
}



int Mage::getCost() {
    return cost;
}

bool Mage::CheckTowerInBlock(int row, int col) {
    return (posM.first == row && posM.second == col);
}

bool Mage::isOutOfRange(shared_ptr<enemy> enemy) {
    if (enemy != nullptr) {
        float tamY = posM.first * TILE_HEIGHT + TILE_HEIGHT / 2 + Y_UPPER_LEFT;
        float tamX = posM.second * TILE_WIDTH + TILE_WIDTH + X_UPPER_LEFT;
        float enemyX = enemy->getBlock().x1;
        float enemyY = enemy->getBlock().y1;
        float distanceSquared = (tamX - enemyX) * (tamX - enemyX) + (tamY - enemyY) * (tamY - enemyY);
        float distance = sqrt(distanceSquared);
        return distance > weaponRange;
    }
    return false;
}

