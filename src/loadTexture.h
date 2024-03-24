#ifndef LOADTEXTURE_H
#define LOADTEXTURE_H

#include "CommonFunc.h"

class loadTexture
{
    public:
        static SDL_Texture* loadT(SDL_Renderer* renderer, string filename);
        static void deallocateTextures();


    private:
        static std::unordered_map<string, SDL_Texture*> umapTexturesLoaded;
};
#endif // LOADTEXTURE_H
