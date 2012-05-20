#ifndef NPC_H__
#define NPC_H__

#include "Character.h"
#include <vector>
#include <deque>
#include <queue>
#include "Action.h"

class Npc : public Character {
 public:
  Npc(Context const& c, std::vector<std::vector<int> > const& map);
  virtual void animate(const std::string& dir, int count = -1);
  virtual void stop();
  void die();
  void tick(float dt);
 private:
  void onDeath(GameEventPointer e, EventDispatcher* dispatcher);
 private:
  std::vector<DisplayObject*> m_sprites;

};

#endif
