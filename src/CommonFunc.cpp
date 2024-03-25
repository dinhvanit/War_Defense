#include "CommonFunc.h"

Map CreateMap()
{
    Map result;
    vector<Block> temps;
    Block temp;
    for (int y = 0; y < nROW; y++)
    {
        temps.clear();
        for (int x = 0; x < nCOL; x++)
        {
            if(x==0 && y ==nROW/2) temp = Block(y, x, 3);
            else if(x==nCOL-1 && y==nROW/2) temp = Block(y, x, 4);
            else{
                temp = Block(y, x, 0);
            }
            temps.push_back(temp);
        }
        result.push_back(temps);
    }
    return result;
}
