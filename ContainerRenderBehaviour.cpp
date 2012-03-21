#include "ContainerRenderBehaviour.h"
#include "IRenderer.h"
#include "DisplayObject.h"

ContainerRenderBehaviour::ContainerRenderBehaviour(std::vector<DisplayObject*> const& children): m_children(children) {
}

void ContainerRenderBehaviour::onRender(IRenderer*, DisplayObject const&) {
  for (std::vector<DisplayObject*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
    (*it)->render();
  }
}

