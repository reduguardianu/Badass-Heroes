#ifndef GAME_H__
#define GAME_H__

#include "Context.h"
#include "Level.h"

class Game {
 public:
  explicit Game(int width, int height, Context const& c);
  ~Game();
  void createWindow();
  void destroy();
  void tick(float dt);
  bool isRunning();
 private:
  Context const& m_context;
  Level m_level;
  bool m_running;
};

#endif
