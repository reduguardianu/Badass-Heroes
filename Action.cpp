#include "Action.h"

const int Action::WALK = 0;
const int Action::OPEN_CHEST = 1;

Action::Action(int type, point p):m_type(type), m_point(p) {
}

int Action::type() const {
  return m_type;
}

point Action::dest() const {
  return m_point;
}
