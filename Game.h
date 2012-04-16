#ifndef GAME_H__
#define GAME_H__

#include "Context.h"
#include "Level.h"
#include "AnimatedSprite.h"
#include <map>
#include "Types.h"
#include "Event.h"
#include "Hero.h"
#include "Npc.h"


class Game: public IEventReceiver {
 public:
  explicit Game(Context& c, char* mapfile = NULL);
  ~Game();
  void createWindow();
  void destroy();
  void tick(float dt);
  bool isRunning();
  void onEvent(const Event& e);
 private:
  Context& m_context;
  Level m_level;
  bool m_running;
  float m_elapsed_time;
  const float FRAME_RATE;
  const float FRAME_TIME;
  Hero* m_hero;
  std::map<Keyboard::KEY, bool> m_keys;
  Npc* m_zombie;
};

#endif
