#ifndef SPELLEVENT_H__
#define SPELLEVENT_H__

#include "GameEvent.h"

class SpellEvent : public GameEvent {
 public:
  explicit SpellEvent( const std::string& type, int x = 0, int y = 0);
  std::string type() const;
 private:
  std::string m_type;
};

#endif 
