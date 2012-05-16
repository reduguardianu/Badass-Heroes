#ifndef UTILS_H__
#define UTILS_H__

#include "Types.h"
#include <cmath>
#include "DisplayObject.h"

namespace Utils {
  point getPositionDiff(point pos, point dest, float dt);
  bool regionHit(int x, int y, DisplayObject* d);
  bool rectHit(int x, int y, Rectangle* r);
}
#endif
