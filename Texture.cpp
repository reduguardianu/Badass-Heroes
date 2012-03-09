#include "Texture.h"

Texture::Texture(GLuint texture, int width, int height): m_texture(texture),
                                                         m_width(width),
                                                         m_height(height) {
                                                         }

GLuint Texture::get() const {
    return m_texture;
}

int Texture::width() const {
    return m_width;
}

int Texture::height() const {
    return m_height;
}
