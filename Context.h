#ifndef CONTEXT_H__
#define CONTEXT_H__

#include "IRenderer.h"
#include "ILogger.h"

class Context {
 public:
 Context(IRenderer* renderer, ILogger* logger): m_renderer(renderer), m_logger(logger) {}
  IRenderer* m_renderer;
  ILogger* m_logger;
};

#endif
