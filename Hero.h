#ifndef HERO_H__
#define HERO_H__

#include "Texture.h"
#include "DisplayObject.h"
#include "Context.h"
#include <vector>
#include "Event.h"
#include "Types.h"
#include <deque>

class Hero : public DisplayObject {
 public:
  Hero(Context const& c, std::vector<std::vector<int> > const& map);
  ~Hero();
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  void onEvent(const Event& e);
  void tick(float dt);
  std::deque<point>* findPath(int x, int y);
 private:
  std::vector<DisplayObject*> m_sprites;
  std::vector<std::vector<int> > const& m_map;
  std::deque<point>* m_path;
};

#endif
