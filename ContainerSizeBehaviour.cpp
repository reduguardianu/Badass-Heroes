#include "ContainerSizeBehaviour.h"

ContainerSizeBehaviour::ContainerSizeBehaviour(std::vector<DisplayObject*> const& children): m_children(children) {
}

int ContainerSizeBehaviour::width() const {
  int minX = 0;
  int maxX = 0;
  for (std::vector<DisplayObject*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
    if ((*it)->x() < minX) {
      minX = (*it)->x();
    }
    if ((*it)->x() + (*it)->width() > maxX) {
      maxX = (*it)->x() + (*it)->width();
    }
  }

  return maxX - minX;

}

int ContainerSizeBehaviour::height() const {
  int minY = 0;
  int maxY = 0;
  for (std::vector<DisplayObject*>::const_iterator it = m_children.begin(); it != m_children.end(); ++it) {
    if ((*it)->y() < minY) {
      minY = (*it)->y();
    }
    if ((*it)->y() + (*it)->height() > maxY) {
      maxY = (*it)->y() + (*it)->height();
    }
  }

  return maxY - minY;

}
