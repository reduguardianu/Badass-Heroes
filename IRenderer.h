#ifndef IRENDERER_H__
#define IRENDERER_H__
#include "Types.h"
#include <string>
class DisplayObject;
class Frame;
class Texture;

class IRenderer {
public:
  virtual void beginFrame() = 0;
  virtual void setSize(float, float) = 0;
  virtual void renderSprite(const DisplayObject&, const Frame*) = 0;
  virtual void renderText(const std::string&, const std::string&, int, int, float = 1.0f) = 0;
  virtual void endFrame() = 0;
  virtual float getWindowWidth() const = 0;
  virtual float getWindowHeight() const = 0;
};

#endif
