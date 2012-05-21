#include "Textfield.h"

Textfield::Textfield(Context const& c, std::string text, std::string font): DisplayObject(c), 
									    m_text(text),
									    m_font(font) {
									    }

void Textfield::render() {
  m_context.renderer->renderText(m_text, m_font, x(), y(), alpha());
}
