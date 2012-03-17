#ifndef ANIMATEDSPRITE_H__
#define ANIMATEDSPRITE_H__

#include <string>
#include "IDrawable.h"
#include "Context.h"
#include "Types.h"

class AnimatedSprite:IDrawable {
 public:
  explicit AnimatedSprite(Context const& c, std::string spriteSheet);
  int x() const;
  int y() const;
  float scaleX() const;
  float scaleY() const;
  const char* texture() const;
  void render();
  void setPosition(int x, int y);
  void setScale(float scale_x, float scale_y);

  void animate(Anim::DIRECTION dir);
  void stop();
 private:
  Context const& m_context;
  std::string m_spritesheet_name;
  int m_x;
  int m_y;
  float m_scale_x;
  float m_scale_y;
  unsigned int m_frame;
  Anim::DIRECTION m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
  
};

#endif
