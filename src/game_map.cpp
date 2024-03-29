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
    SDL_Texture* TowerBar = loadTexture::loadT(renderer, "TowerBar.png");
    SDL_Texture* Archer = loadTexture::loadT(renderer, "archer.png");
    SDL_Texture* Canon = loadTexture::loadT(renderer, "canon.png");
    SDL_Texture* Mage = loadTexture::loadT(renderer, "mage.png");
    //draw TowerBar selection
    SDL_Rect rectbar = {0, 0, X_UPPER_LEFT, SCREEN_HEIGHT};
    SDL_RenderCopy(renderer, TowerBar, NULL, &rectbar);

    SDL_Rect rectArcher = {10, 10, 180, 150};
    SDL_RenderCopy(renderer, Archer, NULL, &rectArcher);

    SDL_Rect rectCanon = {10, 180, 180, 150};
    SDL_RenderCopy(renderer, Canon, NULL, &rectCanon);

    SDL_Rect rectMage = {10,340, 180, 150};
    SDL_RenderCopy(renderer, Mage, NULL, &rectMage);

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
bool GameMap::isValid(int col, int row, int rows, int cols) {
    return (col >= 0 && col < cols && row >= 0 && row < rows);
}
vector<Block> GameMap::findShortestPath(Map& gmap, Block start, Block finish)
{
    int rows = gmap.size();
    int cols = gmap[0].size();

    vector<vector<bool>> visited(rows, vector<bool>(cols, false)); // Đánh dấu các vị trí đã được duyệt
    vector<vector<Block>> parent(rows, vector<Block>(cols, {-1, -1, -1})); // Lưu vị trí cha của mỗi vị trí

    queue<Block> q;
    q.push(start);
    visited[start.row][start.col] = true;

    while (!q.empty()) {
        Block current = q.front();
        q.pop();

        if (current.row == finish.row && current.col == finish.col)
            break;

        int dr[4] = {-1, 0, 1, 0}; // Lên, phải, xuống, trái
        int dc[4] = {0, 1, 0, -1};

        for (int i = 0; i < 4; ++i) {
            int new_row = current.row + dr[i];
            int new_col = current.col + dc[i];
            if ((new_col >= 0 && new_col < cols && new_row >= 0 && new_row < rows) && !visited[new_row][new_col] && gmap[new_row][new_col].isTowerIn != 1) {
                Block next = {new_col, new_row, -1};
                q.push(next);
                visited[new_row][new_col] = true;
                parent[new_row][new_col] = current;
            }
        }
    }

    // Tạo đường đi từ start đến finish
    vector<Block> path;
    Block current = finish;
    while (current.row != -1 && current.col != -1) {
        path.push_back(current);
        current = parent[current.row][current.col];
    }
    reverse(path.begin(), path.end());
    cout << "Duong di ngan nhat" << endl;
    for (const auto& block : path) {
        cout << "(" << block.row << ", " << block.col << ")" << endl;
    }
    return path;
}
