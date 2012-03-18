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
  int x() const;
  int y() const;
  int width() const;
  int height() const;
  float scaleX() const;
  float scaleY() const;
  const Texture* texture() const;
  void setParent(const IDrawable*);
  void render();
  void setPosition(int x, int y);
  void setScale(float scale_x, float scale_y);

  void animate(Anim::DIRECTION dir);
  void stop();
 private:
  Context const& m_context;
  Texture* m_spritesheet;
  int m_x;
  int m_y;
  float m_scale_x;
  float m_scale_y;
  unsigned int m_frame;
  Anim::DIRECTION m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
  const IDrawable* m_parent;
};

#endif
