#ifndef IRENDERER_H__
#define IRENDERER_H__
class IDrawable;

class IRenderer {
public:
  virtual void beginFrame() = 0;
    virtual void renderSprite(const IDrawable&) = 0;
    virtual void endFrame() = 0;
};

#endif
