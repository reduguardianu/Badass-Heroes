#ifndef IRENDERER_H__
#define IRENDERER_H__
class IDrawable;

class IRenderer {
public:
  virtual void beginFrame() = 0;
  virtual void setSize(float, float) = 0;
    virtual void renderSprite(const IDrawable&) = 0;
    virtual void endFrame() = 0;
    virtual float getWindowWidth() const = 0;
    virtual float getWindowHeight() const = 0;
};

#endif
