#include "Button.h"
#include "SpriteSizeBehaviour.h"

Button::Button(Context const& c, std::string active, std::string inactive, std::string text): DisplayObject(c),
											      m_text(text),
											      m_active(false){
  m_active_sprite = new Sprite(m_context, active);
  m_inactive_sprite = new Sprite(m_context, inactive);
  m_active_sprite->setParent(this);
  m_inactive_sprite->setParent(this);

  m_size_behaviour = new SpriteSizeBehaviour(m_active_sprite->frame());
}

void Button::setActive(bool value) {
  m_active = value;
}

void Button::render() {
  if (m_active) {
    m_active_sprite->render();
  }
  else {
    m_inactive_sprite->render();
  }
  m_context.renderer->renderText(m_text, "arial", x(), y());
}

