#include "SpriteSizeBehaviour.h"

SpriteSizeBehaviour::SpriteSizeBehaviour(Frame* f): m_frame(f) {
}

int SpriteSizeBehaviour::width() const {
  return m_frame->width();
}

int SpriteSizeBehaviour::height() const {
  return m_frame->height();
}
