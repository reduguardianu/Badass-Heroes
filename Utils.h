#ifndef UTILS_H__
#define UTILS_H__

#include "Types.h"
#include <cmath>
#include "DisplayObject.h"

namespace Utils {
  extern point directions[4];
  point getPositionDiff(point pos, point dest, float dt);
  bool regionHit(int x, int y, DisplayObject* d);
  bool rectHit(int x, int y, Rectangle* r);
  int taxiDistance(point const& a, point const& b);
}
#endif
