#ifndef SPRITE_H__
#define SPRITE_H__
#include <string>
#include "DisplayObject.h"
#include "Context.h"
#include "Frame.h"

class Sprite : public DisplayObject {
public:
  explicit Sprite(Context const& c, std::string textureName);
  void setUV(float u, float v);
  void setSize(float w, float h);
  float textureWidth() const;
  float textureHeight() const;
  std::string name();
  Frame* frame() const;
 protected:
  Frame* m_frame;
};

#endif
