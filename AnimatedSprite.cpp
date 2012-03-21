#include "AnimatedSprite.h"
#include "TextureFactory.h"
#include "AnimatedRenderBehaviour.h"
#include "AnimatedSizeBehaviour.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(Context const& c, std::string spritesheet): DisplayObject(c),
									   m_frame(0),
									   m_direction(Anim::Up),
									   m_animate(false),
									   m_animation_speed(4),
									   m_spritesheet(NULL) {
  m_spritesheet = TextureFactory::getTexture(spritesheet);

  m_render_behaviour = new AnimatedRenderBehaviour(m_spritesheet, m_frame, m_direction, m_animation_speed);
  m_size_behaviour = new AnimatedSizeBehaviour(m_spritesheet);
}

void AnimatedSprite::animate(Anim::DIRECTION dir) {
  m_animate = true;
  m_frame = 0;
  m_direction = dir;
}

void AnimatedSprite::stop() {
  m_animate = false;
  m_frame = 0;
  m_direction = Anim::Up;
}

void AnimatedSprite::render() {
  DisplayObject::render();
  if (m_animate) {
    m_frame++;
  }
}

