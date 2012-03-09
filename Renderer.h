#ifndef RENDERER_H__
#define RENDERER_H__

#include "IRenderer.h"
#include "TextureFactory.h"
class IDrawable;
//class TextureFactory;

class Renderer: public IRenderer {
public:
    explicit Renderer(float window_width, float window_height);
    void renderSprite(const IDrawable&);
private :
    TextureFactory m_texture_factory;
    float m_window_width;
    float m_window_height;
};


#endif
