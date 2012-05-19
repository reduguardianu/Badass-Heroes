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
#include "Hud.h"
#include "Button.h"

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
  void doGUI();
  bool button(Button* b);
  void endTurn();
  void countFPS(float dt);
 private:
  Context& m_context;
  Level m_level;
  Hud m_hud;
  bool m_running;
  float m_elapsed_time;
  const float FRAME_RATE;
  const float FRAME_TIME;
  std::vector<Hero*> m_heroes;
  std::map<Keyboard::KEY, bool> m_keys;
  Button* m_end_turn;
  Button* m_spell;  
  Button* m_build_spell;
  int m_current_player;
  std::string m_fps_text;
  int m_fps_counter;
  float m_fps_time;
};

#endif
