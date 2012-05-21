#ifndef RENDERER_H__
#define RENDERER_H__

#include "IRenderer.h"
#include "TextureFactory.h"
#include "Types.h"
#include "Frame.h"
#include <map>
#include "include/GL/glfw.h"
class DisplayObject;

class Renderer: public IRenderer {
public:
    explicit Renderer();
    void beginFrame();
    void endFrame();
    void renderSprite(const DisplayObject&, const Frame*);
    void renderText(const std::string& text, const std::string& font, int x, int y, float alpha = 1.0f);
    void setSize(float, float);
    float getWindowWidth() const;
    float getWindowHeight() const;
private:
    bool clip(float x, float y, float width, float height);
    GLuint getTexture(const Frame* frame);
private :
    TextureFactory m_texture_factory;
    float m_window_width;
    float m_window_height;
    std::map<const char*, GLuint> m_textures;
};


#endif
