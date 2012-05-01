#include "Hud.h"
#include <iostream>

Hud::Hud(Context const& c): DisplayObject(c) {
  setBounds(new Rectangle(0, 0, m_context.screen_width, m_context.screen_height));
  m_sprites.push_back(new AnimatedSprite(c, "base"));
  m_sprites.push_back(new AnimatedSprite(c, "headgear_01"));
  m_sprites.push_back(new AnimatedSprite(c, "breastplate_01"));
  m_sprites.push_back(new AnimatedSprite(c, "tights_01"));

  for (int i = 0; i < m_sprites.size(); ++i) {
    addChild(m_sprites.at(i));
    m_sprites.at(i)->setDirection(Animations::down);
    m_sprites.at(i)->setScale(8.0f);
  }
}

void Hud::render() {
  for (int i = 0; i < m_sprites.size(); ++i) {
    m_sprites.at(i)->render();
  }
}


void Hud::onEvent(const Event& e) {
  if (e.event_type == EventType::Resize) {
    setPosition(m_context.screen_width - 250, 0);
    setBounds(new Rectangle(0, 0, m_context.screen_width, m_context.screen_height));
  }
  
}
