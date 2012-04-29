#ifndef NPC_H__
#define NPC_H__

#include "DisplayObject.h"
#include <vector>

class Npc : public DisplayObject {
 public:
  Npc(Context const& c);
  virtual void animate(const std::string& dir, int count = -1);
  virtual void stop();
  void die();
  void tick(float dt);
 private:
  void onDeath(std::string e, EventDispatcher* dispatcher);
 private:
  std::vector<DisplayObject*> m_sprites;
};

#endif
