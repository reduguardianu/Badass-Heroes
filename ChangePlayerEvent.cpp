#include "ChangePlayerEvent.h"
#include "Types.h"

ChangePlayerEvent::ChangePlayerEvent(Character* ch, int x, int y): GameEvent(ET::change_player, x, y), m_character(ch) {
}

Character* ChangePlayerEvent::character() const {
  return m_character;
}
