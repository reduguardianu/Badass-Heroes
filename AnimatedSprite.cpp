#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(Context const& c, std::string spritesheet):m_context(c),
									  m_spritesheet_name(spritesheet),
									  m_x(0),
									  m_y(0),
									  m_scale_x(1.0f),
									  m_scale_y(1.0f),
									  m_animate(false),
									  m_animation_speed(2){
}

int AnimatedSprite::x() const {
  return m_x;
}

int AnimatedSprite::y() const {
  return m_y;
}

float AnimatedSprite::scaleX() const {
  return m_scale_x;
}

float AnimatedSprite::scaleY() const {
    return m_scale_y;
}
const char* AnimatedSprite::texture() const {
    return m_spritesheet_name.c_str();
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
  m_context.renderer->renderSpriteAnimation(*this, (m_frame/m_animation_speed) % 5, m_direction);
  if (m_animate) {
    m_frame++;
  }
}
void AnimatedSprite::setPosition(int x, int y) {
    m_x = x;
    m_y = y;
}
void AnimatedSprite::setScale(float scale_x, float scale_y) {
    m_scale_x = scale_x;
    m_scale_y = scale_y;
}

