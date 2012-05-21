#include "AnimatedSizeBehaviour.h"

AnimatedSizeBehaviour::AnimatedSizeBehaviour(Texture* t): m_texture(t) {
}

int AnimatedSizeBehaviour::width() const {
  return m_texture->width() / 4;
}

int AnimatedSizeBehaviour::height() const {
  return m_texture->height() / 4;
}
