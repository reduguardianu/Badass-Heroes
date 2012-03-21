#include "AnimatedRenderBehaviour.h"
#include "IRenderer.h"
#include "DisplayObject.h"
#include <iostream>

AnimatedRenderBehaviour::AnimatedRenderBehaviour(Texture* t, unsigned int const& frame, Anim::DIRECTION const& dir, unsigned int const& speed):
  m_texture(t),
  m_frame(frame),
  m_direction(dir),
  m_animation_speed(speed) {
  }

void AnimatedRenderBehaviour::onRender(IRenderer* renderer, DisplayObject const& d) {
  renderer->renderSpriteAnimation(d, m_texture, (m_frame / m_animation_speed) % 4, m_direction);
}
