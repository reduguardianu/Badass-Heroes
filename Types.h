#ifndef TYPES_H__
#define TYPES_H__

#include <utility>

namespace Anim {
  enum DIRECTION {
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3
  };
};

typedef std::pair<int, int> point;

#endif 
