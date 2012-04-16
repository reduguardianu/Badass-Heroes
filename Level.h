#ifndef LEVEL_H__
#define LEVEL_H__

#include <string>
#include <vector>
#include "Context.h"
#include "Sprite.h"
#include <map>
#include <vector>
#include "Event.h"
#include "Texture.h"
#include "Tile.h"
#include "Hero.h"
#include "Npc.h"

class Level : public DisplayObject  {
 public:
  explicit Level(Context const& c);
  void loadFromFile(std::string filename);
  void tick(float dt);
  void onEvent(const Event& e);
  ~Level();
  std::vector<std::vector<int> > const& getData();

  void setCurrentPlayer(Hero* hero);
  void addChild(DisplayObject*);
  void spawnNpcs(int count);

 private:
  void initData();
  void moveCamera(float dt);
 private:
  std::vector<std::vector<int> > m_data;
  std::map<Keyboard::KEY, bool> m_keys;
  std::vector<Tile*> m_tiles;
  std::vector<DisplayObject*> m_children;
  int m_level_width;
  int m_level_height;
  Hero* m_hero;
  bool m_camera_moved;
  std::vector<Npc*> m_npcs;

};

#endif
