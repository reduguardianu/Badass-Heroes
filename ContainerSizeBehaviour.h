#ifndef CONTAINERSIZEBEHAVIOUR_H__
#define CONTAINERSIZEBEHAVIOUR_H__

#include "ISizeBehaviour.h"
#include "DisplayObject.h"
#include <vector>

class ContainerSizeBehaviour : public ISizeBehaviour {
 public:
  ContainerSizeBehaviour(std::vector<DisplayObject*> const&);
  int width() const;
  int height() const;

 private:
  std::vector<DisplayObject*> const& m_children;
};

#endif
