#ifndef CHANGEPLAYEREVENT_H__
#define CHANGEPLAYEREVENT_H__

#include "GameEvent.h"
#include "Character.h"

class ChangePlayerEvent : public GameEvent {
 public:
  explicit ChangePlayerEvent( Character* ch, int x = 0, int y = 0);
  Character* character() const;
 private:
  Character* m_character;
  
};

#endif
