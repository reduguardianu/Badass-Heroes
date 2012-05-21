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
  virtual void animate(std::string dir, int count = -1);
  virtual void setDirection(std::string dir);
  virtual void stop();
  void tick(float dt);
  void render();
  void gotoFrame(int frame, int time = -1);
  std::string spritesheet() const;
 protected:
  unsigned int m_frame_nr;
  std::string m_direction;
  bool m_animate;
  unsigned int m_animation_speed;
 private:
  std::map<std::string, std::vector<Frame*> > m_frames;
  int m_counter;
  int m_goto_counter;
  std::string m_spritesheet;
};

#endif
