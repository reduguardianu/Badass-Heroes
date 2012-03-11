#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "IDrawable.h"
#include "Context.h"

class Sprite:IDrawable {
public:
  explicit Sprite(Context const& c, std::string textureName);
    int x() const;
    int y() const;
    float scaleX() const;
    float scaleY() const;
    const char* texture() const;
    void render();
    void setPosition(int x, int y);
    void setScale(float scale_x, float scale_y);
private:
    Context const& m_context;
    std::string m_texture_name;
    int m_x;
    int m_y;
    float m_scale_x;
    float m_scale_y;
};

#endif
