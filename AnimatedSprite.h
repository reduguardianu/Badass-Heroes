#ifndef ANIMATEDSPRITE_H__
#define ANIMATEDSPRITE_H__

#include <string>
#include "IDrawable.h"
#include "Context.h"
#include "Types.h"
#include "Texture.h"

class AnimatedSprite: public IDrawable {
 public:
  explicit AnimatedSprite(Context const& c, std::string spriteSheet);
  virtual int x() const;
  virtual int y() const;
  virtual int width() const;
  virtual int height() const;
  virtual float scaleX() const;
  virtual float scaleY() const;
  virtual const Texture* texture() const;
  virtual void setParent(const IDrawable*);
  virtual void render();
  virtual void setPosition(int x, int y);
  virtual void setScale(float scale_x, float scale_y);

  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
 protected:
  Context const& m_context;
  int m_x;
  int m_y;
  float m_scale_x;
  float m_scale_y;
  unsigned int m_frame;
  Anim::DIRECTION m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
  const IDrawable* m_parent;
 private:
  Texture* m_spritesheet;

};

#endif
