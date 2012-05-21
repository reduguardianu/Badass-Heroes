#ifndef ACTION_H__
#define ACTION_H__

#include "Types.h"

class Action {
 public:
  static const int WALK;
  static const int OPEN_CHEST;
  explicit Action(int, point);
  int type() const;
  point dest() const;
 private:
  int m_type;
  point m_point;

};

#endif
