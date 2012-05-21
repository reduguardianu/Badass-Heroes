#ifndef HERO_H__
#define HERO_H__

#include "Texture.h"
#include "Character.h"
#include "Context.h"
#include <vector>
#include "Event.h"
#include "Types.h"
#include <deque>
#include <set>
#include "Sprite.h"
#include "Figure.h"
#include "Action.h"
#include "Spell.h"

class Hero : public Character {
 public:
  Hero(Context const& c, std::vector<std::vector<int> > const& map, std::string headgear, std::string breastplate, std::string pants);
  ~Hero();
  void animate(const std::string& dir, int count = -1);
  virtual void stop();
  void onEvent(const Event& e);
  void tick(float dt);
  bool isTileVisible(int row, int col) const;
  point getTileOffset() const;
  void gotoFrame(int frame, int time = -1);
  Figure* getAvatar();
  void setState(State::STATE value);
  State::STATE state() const;
  void onAction(Action a);
  void spell(Spell* s);
 private:
  void initVisibleTiles(std::vector<std::vector<int> > const& map);
  void findVisibleTiles();
  int posToTile(float p) const;
  int tileDistance(point const& a, point const& b) const;
  void onSpellCasted(GameEventPointer e, EventDispatcher* dispatcher);
  void clearGuidePath();
  void drawPath(int col, int row);
 private:
  Figure* m_figure;
  Figure* m_avatar;
  std::set<point> m_visible;
  State::STATE m_state;
  std::vector<Sprite*> m_guide_path;
  point m_last_point;
  Spell* m_spell;
};

#endif
