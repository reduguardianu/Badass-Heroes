#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "IDrawable.h"
class IRenderer;

class Sprite:IDrawable {
public:
    explicit Sprite(IRenderer& renderer, std::string textureName);
    int x() const;
    int y() const;
    float scaleX() const;
    float scaleY() const;
    const char* texture() const;
    void render();
    void setPosition(int x, int y);
    void setScale(float scale_x, float scale_y);
private:
    IRenderer& m_renderer;
    std::string m_texture_name;
    int m_x;
    int m_y;
    float m_scale_x;
    float m_scale_y;
};

#endif
