#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "IRenderer.h"
#include "ILogger.h"
#include "Timer.h"

class Context {
 public:
  Context();
  ~Context();

  int screen_width;
  int screen_height;
  const float DEFAULT_SCALE;
  const float TILE_SIZE;
 IRenderer* renderer;
 ILogger* logger;
 Timer* timer;
};

#endif
