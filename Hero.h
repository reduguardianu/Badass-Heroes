#ifndef HERO_H__
#define HERO_H__

#include "Texture.h"
#include "AnimatedSprite.h"
#include "Context.h"
#include <vector>

class Hero : public AnimatedSprite {
 public:
  Hero(Context const& c);
  ~Hero();
  virtual void render();
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  
 private:
  std::vector<AnimatedSprite*> m_sprites;
};

#endif
