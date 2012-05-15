#include "Sprite.h"
#include "SpriteRenderBehaviour.h"
#include "SpriteSizeBehaviour.h"

Sprite::Sprite(Context const& c, std::string textureName): DisplayObject(c) {
  m_frame = new Frame(textureName);
  m_render_behaviour = new SpriteRenderBehaviour(m_frame);
  m_size_behaviour = new SpriteSizeBehaviour(m_frame);
}

void Sprite::setUV(float u, float v) {
  m_frame->setUV(u, v);
}

void Sprite::setSize(float w, float h) {
  m_frame->setSize(w, h);
}

std::string Sprite::name() {
  return m_frame->name();
}

float Sprite::textureWidth() const {
  return m_frame->textureWidth();
}

float Sprite::textureHeight() const {
  return m_frame->textureHeight();
}

Frame* Sprite::frame() const {
  return m_frame;
}




