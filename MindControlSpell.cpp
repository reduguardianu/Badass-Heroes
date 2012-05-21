#include "MindControlSpell.h"
#include <cmath>
#include "SpellEvent.h"

MindControlSpell::MindControlSpell(Context const& c): Spell(c, "yoda") {
}

void MindControlSpell::onEvent(const Event& e) {
  if (e.event_type == EventType::MouseMoved) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    setPosition(x * m_context.TILE_SIZE, y * m_context.TILE_SIZE);
  }
}

void MindControlSpell::tick(float dt) {
  
}

void MindControlSpell::cast(std::pair<int, int> from, std::pair<int, int> to) {
  dispatchEvent(new SpellEvent(SpellType::mind_control, floor(m_x /m_context.TILE_SIZE), floor(m_y / m_context.TILE_SIZE)), this);
}

