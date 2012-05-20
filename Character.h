#ifndef CHARACTER_H__
#define CHARACTER_H__

#include "DisplayObject.h"
#include <vector>
#include <deque>
#include <queue>
#include "Action.h"

class Character : public DisplayObject {
 public:
  Character(Context const& c, std::vector<std::vector<int> > const& map);
  virtual void onAction(Action);
  virtual void tick(float dt);
  virtual void animate(const std::string& dir, int count = -1);  
  bool isMoving() const;
  virtual bool isTileVisible(int row, int col) const;
 protected:
  std::deque<point>* findPath(int x, int y);
 private:
  bool addStartToPath(point start, std::deque<point>* path);
  
 protected:
  std::vector<Action> m_actions;
  std::deque<point>* m_path;
  std::vector<std::vector<bool> > m_seen;
  std::vector<std::vector<int> > const& m_map;
};

#endif
