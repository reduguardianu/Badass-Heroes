#include "Sprite.h"
#include "TextureFactory.h"

Sprite::Sprite(Context const& c, std::string textureName):m_context(c),
                                                             m_texture(NULL),
                                                             m_x(0),
                                                             m_y(0),
                                                             m_scale_x(1.0f),
							     m_scale_y(1.0f),
							     m_parent(NULL){
  m_texture = TextureFactory::getTexture(textureName);
}

int Sprite::x() const {
  int value = m_x;
  if (m_parent) {
    value += m_parent->x();
  }
  return value;
}
int Sprite::y() const {
  int value = m_y;
  if (m_parent) {
    value += m_parent->y();
  }
  return value;
}

int Sprite::width() const {
  return m_texture->width();
}

int Sprite::height() const {
  return m_texture->height();
}

float Sprite::scaleX() const {
    return m_scale_x;
}
float Sprite::scaleY() const {
    return m_scale_y;
}
const Texture* Sprite::texture() const {
    return m_texture;
}
void Sprite::render() {
    m_context.renderer->renderSprite(*this);
}
void Sprite::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}
void Sprite::setScale(float scale_x, float scale_y) {
    m_scale_x = scale_x;
    m_scale_y = scale_y;
}

void Sprite::setParent(const IDrawable* parent) {
  m_parent = parent;
}


