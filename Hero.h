#ifndef HERO_H__
#define HERO_H__

#include "Texture.h"
#include "DisplayObject.h"
#include "Context.h"
#include <vector>
#include "Event.h"
#include "Types.h"
#include <deque>
#include <set>

class Hero : public DisplayObject {
 public:
  Hero(Context const& c, std::vector<std::vector<int> > const& map);
  ~Hero();
  virtual void animate(Anim::DIRECTION dir);
  virtual void stop();
  void onEvent(const Event& e);
  void tick(float dt);
  std::deque<point>* findPath(int x, int y);
  bool isMoving() const;
  bool isTileVisible(int row, int col) const;
  point getTileOffset() const;
 private:
  void initVisibleTiles(std::vector<std::vector<int> > const& map);
  void findVisibleTiles();
  int posToTile(float p) const;
  int tileDistance(point const& a, point const& b) const;
  bool addStartToPath(point start, std::deque<point>* path);
 private:
  std::vector<DisplayObject*> m_sprites;
  std::vector<std::vector<int> > const& m_map;
  std::vector<std::vector<bool> > m_seen;
  std::deque<point>* m_path;
  std::set<point> m_visible;
};

#endif
