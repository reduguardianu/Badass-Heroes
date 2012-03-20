#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "IDrawable.h"
#include "Context.h"
#include "Texture.h"

class Sprite : public IDrawable {
public:
  explicit Sprite(Context const& c, std::string textureName);
    virtual int x() const;
    virtual int y() const;
    virtual int width() const;
    virtual int height() const;
    virtual float scaleX() const;
    virtual float scaleY() const;
    virtual const Texture* texture() const;    
    virtual void render();
    virtual void setPosition(int x, int y);
    virtual void setScale(float scale_x, float scale_y);
    virtual void setParent(const IDrawable*);
 protected:
    Context const& m_context;
    int m_x;
    int m_y;
    float m_scale_x;
    float m_scale_y;
    const IDrawable* m_parent;
 private:
    Texture* m_texture;

};

#endif
