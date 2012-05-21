#include "Button.h"
#include "SpriteSizeBehaviour.h"

const int Button::SELECTED = 0;
const int Button::PRESSED = 1;
const int Button::NORMAL = 2;

Button::Button(Context const& c, std::string normal, std::string pressed, std::string selected, std::string text): DisplayObject(c),
											      m_text(text),
											      m_state(NORMAL){
  m_pressed_sprite = new Sprite(m_context, pressed);
  m_normal_sprite = new Sprite(m_context, normal);
  m_selected_sprite = new Sprite(m_context, selected);
  m_pressed_sprite->setParent(this);
  m_normal_sprite->setParent(this);
  m_selected_sprite->setParent(this);

  m_size_behaviour = new SpriteSizeBehaviour(m_normal_sprite->frame());
}

void Button::setPressed() {
  m_state = PRESSED;
}

void Button::setSelected() {
  m_state = SELECTED;
}

void Button::setNormal() {
  m_state = NORMAL;
}

void Button::render() {
  if (m_state == NORMAL) {
    m_normal_sprite->render();
  }
  else if (m_state == PRESSED) {
    m_pressed_sprite->render();
  }
  else if (m_state == SELECTED) {
    m_selected_sprite->render();
  }
  if (m_text.size()) {
    m_context.renderer->renderText(m_text, "arial", x(), y());
  }
}

