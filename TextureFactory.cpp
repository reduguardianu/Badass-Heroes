#include "TextureFactory.h"
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

TextureFactory::TextureFactory() {}

Texture TextureFactory::getTexture(std::string name) {
    std::map<std::string, Texture>::const_iterator it = m_textures.find(name);
    if (it == m_textures.end()) {
        Texture t = loadTexture(name);
        m_textures.insert(std::make_pair(name, t));
        return t;
    }
    else {
        return it->second;
    }
}

Texture TextureFactory::loadTexture(std::string name) {
    SDL_Surface* textureImage;
    GLuint texture;

    if (!(textureImage=loadImg("assets/"+name))) {
        std::cerr << "Failed to load texture " << name << ". Exiting" << std::endl;
        //TODO: do sth meaningful
        throw 1;
    }

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLint noOfColors = textureImage->format->BytesPerPixel;
    GLenum textureFormat;
    if (noOfColors == 4) {
        if (textureImage->format->Rmask == 0x000000ff) {
            textureFormat = GL_RGBA;
        }
        else {
            textureFormat = GL_BGRA;
        }
    }
    else {
        if (textureImage->format->Rmask == 0x0000ff) {
            textureFormat = GL_RGB;
        }
        else {
            textureFormat = GL_BGR;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, 4, textureImage->w, textureImage->h, 0, textureFormat, GL_UNSIGNED_BYTE, textureImage->pixels);

    Texture return_value(texture, textureImage->w, textureImage->h);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    if (textureImage) {
        SDL_FreeSurface(textureImage);
    }

    return return_value;
}

SDL_Surface* TextureFactory::loadImg(std::string filename) {
    FILE *file = NULL;

    file = fopen(filename.c_str(), "r");

    if (file) {
        fclose(file);
        return IMG_Load(filename.c_str());
    }
    return NULL;
}
