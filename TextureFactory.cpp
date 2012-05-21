#include "TextureFactory.h"
#include "include/SDL/SDL.h"
#include "include/SDL/SDL_image.h"
#include "include/GL/glfw.h"
#include <iostream>

std::map<std::string, Texture*> TextureFactory::m_textures;

Texture* TextureFactory::getTexture(std::string name) {
    std::map<std::string, Texture*>::const_iterator it = m_textures.find(name);
    if (it == m_textures.end()) {
      Texture* t = new Texture("../assets/" + name);
      m_textures.insert(std::make_pair(name, t));
      return t;
    }
    else {
        return it->second;
    }
}


