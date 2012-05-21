#include "Frame.h"
#include "TextureFactory.h"

Frame::Frame(std::string name): m_texture(NULL),
				m_u(0.0f),
				m_v(0.0f),
				m_width(0),
				m_height(0),
				m_repeat(false) {
  if (name.size()) {
    m_texture = TextureFactory::getTexture(name);
    m_width = m_texture->width();
    m_height = m_texture->height();
  }
  
  
}

int Frame::width() const {
  return m_width;
}

int Frame::height() const {
  return m_height;
}

int Frame::textureWidth() const {
  return m_texture->width();
}

int Frame::textureHeight() const {
  return m_texture->height();
}

const char* Frame::name() const {
  return m_texture->name();
}

int Frame::redMask() const {
  return m_texture->redMask();
}

void* Frame::pixels() const {
  return m_texture->pixels();
}

int Frame::numberOfColors() const {
  return m_texture->numberOfColors();
}

float Frame::u() const {
  return m_u;
}

float Frame::v() const {
  return m_v;
}

void Frame::setSize(float w, float h) {
  m_width = w;
  m_height = h;
}

void Frame::setUV(float u, float v) {
  m_u = u;
  m_v = v;
}
