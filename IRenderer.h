#ifndef IRENDERER_H__
#define IRENDERER_H__
class IDrawable;

class IRenderer {
public:
    virtual void renderSprite(const IDrawable&) = 0;
};

#endif
