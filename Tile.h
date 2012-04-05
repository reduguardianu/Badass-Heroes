#ifndef TILE_H__
#define TILE_H__

#include <vector>
#include "Sprite.h"

class Tile : public Sprite {
 public:
  explicit Tile(Context const& c, std::string textureName, int row, int column, std::vector<std::vector<int> > const& map);
  void tick(float dt);
  int row() const;
  int column() const;
  void setVisible(bool);
  void render();
 private:
  int up();
  int right();
  int down();
  int left();
 private:
  int m_row;
  int m_column;
  std::vector<std::vector<int> > const& m_map;
  std::pair<float, float> m_uvs[2][2][2][2];
  bool m_visible;
  Sprite* m_darkness;
};

#endif
