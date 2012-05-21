#ifndef GAMEEVENT_H__
#define GAMEEVENT_H__

#include <string>

class GameEvent {
 public:
  explicit GameEvent(std::string name, int x = 0, int y = 0);
  std::string name() const;
  int x() const;
  int y() const;
  virtual ~GameEvent();
 private:
  std::string m_name;
  int m_x;
  int m_y;
};

#endif 
