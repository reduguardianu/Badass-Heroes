#ifndef FRAME_H__
#define FRAME_H__

#include "Texture.h"
#include <string>

class Frame {
 public:
  explicit Frame(std::string name);
  
  int width() const;
  int height() const;
  int textureWidth() const;
  int textureHeight() const;
  const char* name() const;
  int redMask() const;
  void *pixels() const;
  int numberOfColors() const;
  
  float u() const;
  float v() const;
  void setSize(float w, float h);
  void setUV(float u, float v);
 private:
  Texture* m_texture;
  float m_u;
  float m_v;
  int m_width;
  int m_height;
  bool m_repeat;
};

#endif
