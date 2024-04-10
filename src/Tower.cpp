#include "Tower.h"

const float Tower::weaponRange = 200.0f;


Tower::Tower(SDL_Renderer* renderer, pos _pos):
    posM (_pos), damage(1), targetEnemy(nullptr)
{
    textureTower = loadTexture::loadT(renderer, "archer.png");
}
//
//Tower::~Tower()
//{
//    dtor
//}

void Tower::updateTarget(SDL_Renderer* renderer, float dT, vector<shared_ptr<enemy>>& listEnemys) {
    float closestDistance=weaponRange;
//    cout << "dem con bo"<<endl;
//    cout << "vi tri dat thap ===="<<posM.first <<" "<<posM.second<<endl;
    float tamY=posM.first*TILE_HEIGHT+TILE_HEIGHT/2+Y_UPPER_LEFT;
    float tamX=posM.second*TILE_WIDTH+TILE_WIDTH+X_UPPER_LEFT;
    for (const auto& enemy : listEnemys) {
        float distanceSquared = (tamX - enemy->getBlock().x1) * (tamX - enemy->getBlock().x1) +
                                (tamY - enemy->getBlock().y1) * (tamY - enemy->getBlock().y1);
        float distance = sqrt(distanceSquared);

        cout << distance <<" khoang cach "<<endl;
        if (distance <= closestDistance) {
//            closestDistanceSquared = distanceSquared;
            closestDistance=distance;
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
            cout <<"kill enemy ========" <<endl;
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
