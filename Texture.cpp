#include "Texture.h"
#include "include/SDL/SDL.h"
#include "include/SDL/SDL_image.h"
#include <iostream>
#include <cstdio>

Texture::Texture(std::string name): m_name(name),
				    m_texture(NULL) {
  m_texture = load(m_name);
  if (m_texture == NULL) {
    throw "no textures";
  }
}

SDL_Surface* Texture::load(std::string name) {
    FILE *file = NULL;

    file = fopen(name.c_str(), "r");

    if (file) {
      std::cout << "Found file: " << name << std::endl;
        fclose(file);
        return IMG_Load(name.c_str());
    }

    std::cerr << "No file: " << name << std::endl;
    return NULL;
}

const char* Texture::name() const {
  return m_name.c_str();
}

int Texture::numberOfColors() const {
  if (m_texture) {
    return m_texture->format->BytesPerPixel;
  }

  return 0;
}

int Texture::redMask() const {
  if (m_texture) {
    return m_texture->format->Rmask;
  }

  return 0;
}

int Texture::width() const {
  if (m_texture) {
    return m_texture->w;
  }
  
  return 0;
}

int Texture::height() const {
  if (m_texture) {
    return m_texture->h;
  }

  return 0;
}

void* Texture::pixels() const {
  if (m_texture) {
    return m_texture->pixels;
  }

  return NULL;
}
