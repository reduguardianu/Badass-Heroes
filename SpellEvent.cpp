#include "SpellEvent.h"
#include "Types.h"

SpellEvent::SpellEvent(const std::string& type, int x, int y): GameEvent(ET::spell, x, y), m_type(type) {
}

std::string SpellEvent::type() const {
  return m_type;
}

