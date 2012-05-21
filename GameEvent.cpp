#include "GameEvent.h"

GameEvent::GameEvent(std::string name, int x, int y):m_name(name),
						     m_x(x),
						     m_y(y) {
						     }

std::string GameEvent::name() const {
  return m_name;
}

int GameEvent::x() const {
  return m_x;
}

int GameEvent::y() const {
  return m_y;
}

GameEvent::~GameEvent() {
}
