#ifndef CHARACTER_H__
#define CHARACTER_H__

#include "DisplayObject.h"
#include "Textfield.h"
#include <vector>
#include <deque>
#include <queue>
#include "Action.h"
#include "Sprite.h"

class Character : public DisplayObject {
 public:
  Character(Context const& c, int health, std::vector<std::vector<int> > const& map);
  virtual void onAction(Action);
  virtual void tick(float dt);
  virtual void animate(const std::string& dir, int count = -1);  
  bool isMoving() const;
  virtual bool isTileVisible(int row, int col) const;
  void damage(int value);
  ~Character();
  int health() const;
 protected:
  std::deque<point>* findPath(int x, int y);
 protected:
  std::vector<Action> m_actions;
  std::deque<point>* m_path;
  std::vector<std::vector<bool> > m_seen;
  std::vector<std::vector<int> > const& m_map;
  int m_health;
 private:
  bool addStartToPath(point start, std::deque<point>* path);
  void notifications(float dt);
 private:
  std::vector<std::pair<Sprite*, Textfield*> > m_notifications;
};

#endif
