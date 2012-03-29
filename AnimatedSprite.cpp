#include "AnimatedSprite.h"
#include "TextureFactory.h"
#include "SpriteRenderBehaviour.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(Context const& c, std::string spritesheet): Sprite(c, spritesheet),
									   m_frame_nr(0),
									   m_direction(Anim::Up),
									   m_animate(false),
									   m_animation_speed(4) {

  m_frame->setSize(32, 32);
  Anim::DIRECTION dirs[] = {Anim::Up, Anim::Down, Anim::Left, Anim::Right};

  for (int i = 0; i < 4; ++i) {

    std::vector<Frame*> v;
    for (int j = 0; j < 4; ++j) {
      Frame* f = new Frame(spritesheet);
      f->setUV(0.25 * j, 0.25 * i);
      f->setSize(32, 32);
      //      setScale(2, 2);
      v.push_back(f);
    }
    m_frames.insert(std::make_pair(dirs[i], v));
  }

  
}

void AnimatedSprite::animate(Anim::DIRECTION dir) {
  m_animate = true;
  m_frame_nr = 0;
  m_direction = dir;
}

void AnimatedSprite::stop() {
  m_animate = false;
  m_frame_nr = 0;
  m_direction = Anim::Up;
}

void AnimatedSprite::render() {
  dynamic_cast<SpriteRenderBehaviour*>(m_render_behaviour)->setFrame(m_frames.at(m_direction).at((m_frame_nr / m_animation_speed) % 4));
  Sprite::render();
  if (m_animate) {
    m_frame_nr++;
  }
}

