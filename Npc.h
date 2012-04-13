#ifndef NPC_H__
#define NPC_H__

#include "DisplayObject.h"
#include <vector>

class Npc : public DisplayObject {
 public:
  Npc(Context const& c);
  virtual void animate(const std::string& dir);
  virtual void stop();
  void tick(float dt);
 private:
  std::vector<DisplayObject*> m_sprites;
};

#endif
