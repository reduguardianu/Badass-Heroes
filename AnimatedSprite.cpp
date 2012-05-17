#include "AnimatedSprite.h"
#include "TextureFactory.h"
#include "SpriteRenderBehaviour.h"
#include <iostream>
#include "AnimationParser.h"

AnimatedSprite::AnimatedSprite(Context const& c, std::string spritesheet): Sprite(c, spritesheet + ".png"),
									   m_frame_nr(0),
									   m_direction(Animations::up),
									   m_animate(false),
									   m_animation_speed(4),
									   m_counter(-1),
									   m_goto_counter(-1),
									   m_spritesheet(spritesheet) {


  AnimationParser parser;
  parser.parse(spritesheet + ".txt");

  m_frame->setSize(parser.frame_width, parser.frame_height);

  
  for (AnimationDescription::iterator it = parser.m_animations.begin(); it != parser.m_animations.end(); ++it) {
    std::vector<Frame*> frames;
    for (std::vector<std::pair<float, float> >::iterator jt = it->second.begin(); jt != it->second.end(); ++jt) {
      Frame* f = new Frame(spritesheet + ".png");
      f->setUV(jt->first, jt->second);
      f->setSize(parser.frame_width, parser.frame_height);
      setScale(m_context.TILE_SIZE / parser.frame_width);
      frames.push_back(f);
    }

    m_frames.insert(std::make_pair(it->first, frames));
  }

  
}

std::string AnimatedSprite::spritesheet() const {
  return m_spritesheet;
}

void AnimatedSprite::animate(std::string dir, int count) {
  m_animate = true;
  m_counter = count;
  if (dir != m_direction) {
    m_frame_nr = 0;
    m_direction = dir;
  }
}

void AnimatedSprite::gotoFrame(int frame, int time) {
  m_frame_nr = frame * m_animation_speed;
  m_goto_counter = time * m_animation_speed;
}

void AnimatedSprite::setDirection(std::string dir) {
  m_direction = dir;
}

void AnimatedSprite::stop() {
  if (m_animate) {
    m_animate = false;
    m_frame_nr = 0;
  }
}

void AnimatedSprite::tick(float dt) {
  int current_frame = (m_frame_nr / m_animation_speed) % m_frames.at(m_direction).size();
  int next_frame = ((m_frame_nr + 1) / m_animation_speed) % m_frames.at(m_direction).size();
  if (m_animate && next_frame == 0 && next_frame < current_frame && m_counter > 0) {
    m_counter--;
    if (m_counter == 0) {
      stop();
      dispatchEvent(GameEvent("animationfinish"), this);
    }
  }
}

void AnimatedSprite::render() {
  int current_frame = (m_frame_nr / m_animation_speed) % m_frames.at(m_direction).size();
  dynamic_cast<SpriteRenderBehaviour*>(m_render_behaviour)->setFrame(m_frames.at(m_direction).at(current_frame));
  Sprite::render();
  if (m_animate) {
    m_frame_nr++;
  }
  else if (m_goto_counter >=0) {
    m_goto_counter--;
    if (m_goto_counter == 0) {
      m_frame_nr = 0;
    }
  }
}

