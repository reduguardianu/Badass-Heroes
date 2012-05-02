#include "Hud.h"
#include <iostream>

Hud::Hud(Context const& c): DisplayObject(c),
			    m_current_avatar(NULL) {
  setBounds(new Rectangle(0, 0, m_context.screen_width, m_context.screen_height));
}

void Hud::setAvatar(Figure* figure) {
  if (m_current_avatar && m_current_avatar->parent()) {
    m_current_avatar->parent()->removeChild(m_current_avatar);
  }
  m_current_avatar = figure;
  addChild(m_current_avatar);
}

void Hud::render() {
  if (m_current_avatar != NULL) {
    m_current_avatar->render();
  }
}


void Hud::onEvent(const Event& e) {
  if (e.event_type == EventType::Resize) {
    setPosition(m_context.screen_width - 250, 0);
    setBounds(new Rectangle(0, 0, m_context.screen_width, m_context.screen_height));
  }
  
}
