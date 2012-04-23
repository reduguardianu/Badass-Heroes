#include "Utils.h"

point Utils::getPositionDiff(point pos, point dest, float dt) {
  point result;
  result.first = 0;
  result.second = 0;
  float dx = dest.first - pos.first;
  float dy = dest.second - pos.second;

  if (fabs(dx) < 2 && fabs(dy) < 2) {
    result.first = dx;
    result.second = dy;
  }
  else {
    float dv = 200 * dt / 1000.f;
    if (fabs(dv) > fabs(dx)) {
      result.first = dx;
    }
    else if (dx > 0) {
      result.first = dv;
    }
    else if (dx < 0) {
      result.first = -dv;
    }
      
    if (fabs(dv) > fabs(dy)) {
      result.second = dy;
    }
    else if (dy > 0) {
      result.second = dv;
    }
    else if (dy < 0) {
      result.second = -dv;
    }
  }
    
  return result;
}
