#ifndef TEXTUREFACTORY_H__
#define TEXTUREFACTORY_H__

#include <string>
#include <map>
#include "Texture.h"
#include <SDL/SDL.h>

class TextureFactory {
public:
    explicit TextureFactory();
    Texture getTexture(std::string name);
private:
    Texture loadTexture(std::string name);
    SDL_Surface* loadImg(std::string filename);

    std::map<std::string, Texture> m_textures;
};

#endif
