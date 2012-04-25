#include "DisplayObject.h"

DisplayObject::DisplayObject(Context const& c): m_context(c),
						m_x(0),
						m_y(0),
						m_z(0.0f),
						m_scale_x(1.0f),
						m_scale_y(1.0f),
						m_parent(NULL),
						m_alpha(1.0f),
						m_render_behaviour(NULL),
						m_rotation(0.f) {
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

void DisplayObject::setZ(float value) {
  m_z = value;
}

float DisplayObject::z() const {
  return m_z;
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

float DisplayObject::alpha() const {
  return m_alpha;
}

float DisplayObject::rotation() const {
  return m_rotation;
}

void DisplayObject::tick(float dt) {
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

void DisplayObject::setParent(DisplayObject* parent) {
  m_parent = parent;
}

void DisplayObject::setAlpha(float value) {
  m_alpha = value;
}

DisplayObject::~DisplayObject() {
  if (m_render_behaviour) {
    delete m_render_behaviour;
  }
  if (m_size_behaviour) {
    delete m_size_behaviour;
  }
}

void DisplayObject::addChild(DisplayObject* child) {
  child->setParent(this);
  m_children.push_back(child);
}

void DisplayObject::removeChild(DisplayObject* child) {
  child->setParent(NULL);			
  for (std::vector<DisplayObject*>::iterator it = m_children.begin(); it != m_children.end(); ++it) {
    if (*it == child) {
      m_children.erase(it, it + 1);
      return;
    }
  }
}


void DisplayObject::setRotation(float value) {
  m_rotation = value;
}
