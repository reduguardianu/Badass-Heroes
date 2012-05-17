#ifndef TILE_H__
#define TILE_H__

#include <vector>
#include "Sprite.h"
#include "EventDispatcher.h"
#include "Chest.h"
#include "Action.h"

class Tile : public Sprite {
 public:
  explicit Tile(Context const& c, std::string textureName, std::string shadowTexture, int row, int column, std::vector<std::vector<int> > const& map, std::vector<std::vector<int> > const& destroyed);
  void tick(float dt);
  int row() const;
  int column() const;
  bool visible() const;
  void setVisible(bool);
  void render();
  void setDarknessOffset(point p);
  void setNeighbours(std::vector<Tile*> neigbours);
  bool destroyed() const;
  void onDestroy();
  Action action();
  void openChest();
 private:
  bool up();
  bool right();
  bool down();
  bool left();
  
  bool map_up();
  bool map_right();
  bool map_down();
  bool map_left();
  bool horizontal();
  void onDestroyed(GameEvent, EventDispatcher*);
 private:
  int m_row;
  int m_column;
  std::vector<std::vector<int> > const& m_map;
  std::pair<float, float> m_uvs[2][2][2][2];
  std::pair<float, float> m_shadow_uvs[2][2][2][2];
  bool m_visible;  
  Sprite* m_shadow;
  Sprite* m_darkness;
  std::vector<Tile*> m_neighbours;
  std::vector<std::vector<int> > const& m_destroyed;
  Sprite* m_destroyed_left;
  Sprite* m_destroyed_right;
  Sprite* m_destroyed_up;
  Sprite* m_destroyed_down;
  Sprite* m_torch;
  Sprite* m_dead;
  Chest* m_chest;
  Action* m_action;
};

#endif
