#include "SpriteSizeBehaviour.h"

SpriteSizeBehaviour::SpriteSizeBehaviour(Texture* t): m_texture(t) {
}

int SpriteSizeBehaviour::width() const {
  return m_texture->width();
}

int SpriteSizeBehaviour::height() const {
  return m_texture->height();
}
