#ifndef TEXTUREFACTORY_H__
#define TEXTUREFACTORY_H__

#include <string>
#include <map>
#include "Texture.h"
#include "include/SDL/SDL.h"

class TextureFactory {
public:
    static Texture* getTexture(std::string name);
private:
    static std::map<std::string, Texture*> m_textures;
};

#endif
