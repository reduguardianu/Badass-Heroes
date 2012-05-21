#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "IRenderer.h"
#include "ILogger.h"
#include "Timer.h"

struct UIState
{
  int mousex;
  int mousey;
  int mousedown;

  int hot;
  int active;
  int last;

UIState():mousex(0), mousey(0), mousedown(0), hot(0), active(0), last(0) {};
};

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
 UIState uistate;
};

#endif
