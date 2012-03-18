#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "IDrawable.h"
#include "Context.h"
#include "Texture.h"

class Sprite : public IDrawable {
public:
  explicit Sprite(Context const& c, std::string textureName);
    int x() const;
    int y() const;
    int width() const;
    int height() const;
    float scaleX() const;
    float scaleY() const;
    const Texture* texture() const;    
    void render();
    void setPosition(int x, int y);
    void setScale(float scale_x, float scale_y);
    void setParent(const IDrawable*);
private:
    Context const& m_context;
    Texture* m_texture;
    int m_x;
    int m_y;
    float m_scale_x;
    float m_scale_y;
    const IDrawable* m_parent;
};

#endif
