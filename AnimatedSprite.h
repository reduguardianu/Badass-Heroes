#ifndef ANIMATEDSPRITE_H__
#define ANIMATEDSPRITE_H__

#include <string>
#include "DisplayObject.h"
#include "Context.h"
#include "Types.h"
#include "Texture.h"

class AnimatedSprite: public DisplayObject {
 public:
  explicit AnimatedSprite(Context const& c, std::string spriteSheet);
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  void render();
 protected:
  unsigned int m_frame;
  Anim::DIRECTION m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
 private:
  Texture* m_spritesheet;

};

#endif
