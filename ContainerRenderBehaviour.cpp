#include "ContainerRenderBehaviour.h"
#include "IRenderer.h"
#include "DisplayObject.h"
#include <algorithm>

bool compareZ(DisplayObject* lhs, DisplayObject* rhs) {
  return (lhs->z() < rhs->z());
}

ContainerRenderBehaviour::ContainerRenderBehaviour(std::vector<DisplayObject*>& children): m_children(children) {
}

void ContainerRenderBehaviour::onRender(IRenderer*, DisplayObject const&) {
  std::stable_sort(m_children.begin(), m_children.end(), compareZ);
  for (std::vector<DisplayObject*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
    (*it)->render();
  }
}

