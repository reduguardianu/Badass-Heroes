#ifndef ANIMATEDSPRITE_H__
#define ANIMATEDSPRITE_H__

#include <string>
#include "Sprite.h"
#include "Context.h"
#include "Types.h"
#include "Texture.h"
#include <map>
#include <vector>

class AnimatedSprite: public Sprite {
 public:
  explicit AnimatedSprite(Context const& c, std::string spriteSheet);
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  void render();
 protected:
  unsigned int m_frame_nr;
  Anim::DIRECTION m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
 private:
  std::map<Anim::DIRECTION, std::vector<Frame*> > m_frames;
};

#endif
