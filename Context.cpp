#include "Context.h"
#include "Renderer.h"
#include "StandardLogger.h"


Context::Context():DEFAULT_SCALE(2.0f),
		   TILE_SIZE(32.0f * DEFAULT_SCALE) {
  renderer = new Renderer();
  logger = new StandardLogger();
  timer = new Timer();
}

Context::~Context() {
  delete renderer;
  delete logger;
  delete timer;
}
