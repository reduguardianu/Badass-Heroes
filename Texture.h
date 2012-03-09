#ifndef TEXTURE_H__
#define TEXTURE_H__
#include <GL/gl.h>

class Texture {
public:
    explicit Texture(GLuint texture, int width, int height);
    GLuint get() const;
    int width() const;
    int height() const;
private:
    GLuint m_texture;
    int m_width;
    int m_height;
};

#endif
