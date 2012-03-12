#include "Context.h"
#include "Renderer.h"
#include "StandardLogger.h"

Context::Context() {
  renderer = new Renderer();
  logger = new StandardLogger();
  timer = new Timer();
}

Context::~Context() {
  delete renderer;
  delete logger;
  delete timer;
}
