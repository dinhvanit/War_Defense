#include "loadTexture.h"

unordered_map<string, SDL_Texture*> loadTexture::umapTexturesLoaded;

SDL_Texture* loadTexture::loadT(SDL_Renderer* renderer, string filename) {
    if (filename != "") {
        auto found = umapTexturesLoaded.find(filename);

        if (found != umapTexturesLoaded.end()) {
            return found->second;
        }
        else {
            string filepath = "assets/images/" + filename;

            // Load the image using SDL_image
            SDL_Surface* surfaceTemp = IMG_Load(filepath.c_str());
            if (surfaceTemp != nullptr) {
                // The surface was created successfully, so attempt to create a texture with it.
                SDL_Texture* textureOutput = SDL_CreateTextureFromSurface(renderer, surfaceTemp);
                // Free the surface because it's no longer needed.
                SDL_FreeSurface(surfaceTemp);

                if (textureOutput != nullptr) {
                    SDL_SetTextureBlendMode(textureOutput, SDL_BLENDMODE_BLEND);
                    umapTexturesLoaded[filename] = textureOutput;
                    return textureOutput;
                }
            }
        }
    }
    return nullptr;
}
void loadTexture::deallocateTextures() {
    //Destroy all the textures
    while (umapTexturesLoaded.empty() == false) {
        auto it = umapTexturesLoaded.begin();
        if (it->second != nullptr)
            SDL_DestroyTexture(it->second);

        umapTexturesLoaded.erase(it);
    }
}
