#include "game_map.h"


void GameMap::DrawMap(SDL_Renderer* renderer)
{
    Map mp = CreateMap();
//    for (int y = 0; y < nROW; y++) {
//        for (int x = 0; x < nCOL; x++) {
//            cout <<"("<< mp[y][x].x1<<","<<mp[y][x].y1<<") "<<mp[y][x].isTowerIn<<endl;
//        }
//    }
    SDL_Texture* tile1 = loadTexture::loadT(renderer, "Frontyard1.jpg");
    SDL_Texture* tile2 = loadTexture::loadT(renderer, "Frontyard2.jpg");
    SDL_Texture* tileStart = loadTexture::loadT(renderer, "Start.jpg");
    SDL_Texture* tileFinish = loadTexture::loadT(renderer, "Finish.jpg");
    SDL_Texture* TowerBar = loadTexture::loadT(renderer, "StatusBar.png");
    SDL_Texture* Title = loadTexture::loadT(renderer, "Title.png");
//    SDL_Texture* Archer = loadTexture::loadT(renderer, "archer.png");
//    SDL_Texture* Canon = loadTexture::loadT(renderer, "canon.png");
//    SDL_Texture* Mage = loadTexture::loadT(renderer, "mage.png");
    //draw TowerBar selection
    SDL_Rect rectbar = {0, 0, X_UPPER_LEFT, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, TowerBar, NULL, &rectbar);
    //draw title
    SDL_Rect rectTitle ={X_UPPER_LEFT, 0, SCREEN_WIDTH-X_UPPER_LEFT, Y_UPPER_LEFT};
    SDL_RenderCopy(renderer, Title, NULL, &rectTitle);
//    SDL_Rect rectArcher = {10, 10, 180, 150};
//    SDL_RenderCopy(renderer, Archer, NULL, &rectArcher);
//
//    SDL_Rect rectCanon = {10, 180, 180, 150};
//    SDL_RenderCopy(renderer, Canon, NULL, &rectCanon);
//
//    SDL_Rect rectMage = {10,340, 180, 150};
//    SDL_RenderCopy(renderer, Mage, NULL, &rectMage);

    for (int y = 0; y < nROW; y++) {
        for (int x = 0; x < nCOL; x++) {
            SDL_Rect rect = { x * TILE_WIDTH+X_UPPER_LEFT, y * TILE_HEIGHT+Y_UPPER_LEFT, TILE_WIDTH, TILE_HEIGHT };
            if(x==0 && y ==nROW/2) SDL_RenderCopy(renderer, tileStart, NULL, &rect);
            else if(x==nCOL-1 && y==nROW/2) SDL_RenderCopy(renderer, tileFinish, NULL, &rect);
            else{
                if ((x + y) % 2 == 0){
                SDL_RenderCopy(renderer, tile1, NULL, &rect);
            }
                else{
                SDL_RenderCopy(renderer, tile2, NULL, &rect);
                }
            }
        }
    }
}


pos GameMap::getBlockInMap(int x, int y)
{
//    cout << x << " "<<y <<"---------"<<endl;
    pos result;
//    if(x>X_UPPER_LEFT && y>Y_UPPER_LEFT){
        result.first = (y-Y_UPPER_LEFT)/TILE_HEIGHT;//tọa độ row
        result.second = (x-X_UPPER_LEFT)/TILE_WIDTH;//tọa độ col
    //    cout << result.first << " "<<result.second<<"---------"<<endl;
//    }
    return result;
}


bool GameMap::isValid(int col, int row, int nROW, int nCOL) {
    return (col >= 0 && col < nCOL && row >= 0 && row < nROW);
}
vector<Block> GameMap::findShortestPath(Map& gmap, Block start, Block finish)
{
    vector<vector<bool>> visited(nROW, vector<bool>(nCOL, false));
    vector<vector<Block>> parent(nROW, vector<Block>(nCOL, {-1, -1, -1}));

    queue<Block> q;
    q.push(start);
    visited[start.row][start.col] = true;

    while (!q.empty()) {
        Block current = q.front();
        q.pop();


        int dr[4] = {0, -1, 1, 0};
        int dc[4] = {1, 0, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int new_row = current.row + dr[i];
            int new_col = current.col + dc[i];

            if (isValid(new_col, new_row, nROW, nCOL) && !visited[new_row][new_col] && gmap[new_row][new_col].isTowerIn != 1) {
                Block next = {new_row, new_col, -1};
                q.push(next);
                visited[new_row][new_col] = true;
                parent[new_row][new_col] = current;
            }
        }
    }

    vector<Block> path;
    Block current = finish;
    while (current.row != -1 && current.col != -1) {
        path.push_back(current);
        current = parent[current.row][current.col];
    }
    reverse(path.begin(), path.end());
    return path;
}
bool GameMap::ConDuong(Map gmap)
{
    Block start = gmap[nROW / 2][0]; // Lấy start từ CreateMap()
    Block finish = gmap[nROW / 2][nCOL - 1]; // Lấy finish từ CreateMap()
    vector<Block> shortestPath = GameMap::findShortestPath(gmap, start, finish);
    if(shortestPath.size()>1) return true;
    return false;
}
