#include "DisplayObject.h"

DisplayObject::DisplayObject(Context const& c): m_context(c),
						m_x(0),
						m_y(0),
						m_scale_x(1.0f),
						m_scale_y(1.0f),
						m_parent(NULL),
						m_render_behaviour(NULL) {
}

int DisplayObject::x() const {
  int value = static_cast<int>(m_x);
  if (m_parent) {
    value += m_parent->x();
  }
  return value;
}

int DisplayObject::y() const {
  int value = static_cast<int>(m_y);
  if (m_parent) {
    value += m_parent->y();
  }
  return value;
}

float DisplayObject::scaleX() const {
  return m_scale_x;
}

float DisplayObject::scaleY() const {
  return m_scale_y;
}

const DisplayObject* DisplayObject::parent() const {
  return m_parent;
}

int DisplayObject::width() const {
  return m_size_behaviour->width();
}

int DisplayObject::height() const {
  return m_size_behaviour->height();
}

void DisplayObject::render() {
  m_render_behaviour->onRender(m_context.renderer, *this);
}

void DisplayObject::setPosition(int x, int y) {
  m_x = x;
  m_y = y;
}

void DisplayObject::setScale(float scale) {
  setScale(scale, scale);
}

void DisplayObject::setScale(float scale_x, float scale_y) {
  m_scale_x = scale_x;
  m_scale_y = scale_y;
}

void DisplayObject::setParent(const DisplayObject* parent) {
  m_parent = parent;
}

DisplayObject::~DisplayObject() {
  if (m_render_behaviour) {
    delete m_render_behaviour;
  }
  if (m_size_behaviour) {
    delete m_size_behaviour;
  }
}
