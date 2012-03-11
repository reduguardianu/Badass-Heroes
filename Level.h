#ifndef LEVEL_H__
#define LEVEL_H__

#include <string>
#include <vector>
#include "Context.h"
#include "Sprite.h"

class Level {
 public:
  explicit Level(Context const& c);
  void loadFromFile(std::string filename);
  void render();
  void tick(float dt);
  ~Level();
 private:
  void initData();
  std::vector<Sprite*> m_children;
  std::vector<std::vector<int> > m_data;
  int m_width;
  int m_height;
  Context const& m_context;
};

#endif
