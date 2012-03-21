#ifndef HERO_H__
#define HERO_H__

#include "Texture.h"
#include "DisplayObject.h"
#include "Context.h"
#include <vector>

class Hero : public DisplayObject {
 public:
  Hero(Context const& c);
  ~Hero();
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  
 private:
  std::vector<DisplayObject*> m_sprites;
};

#endif
