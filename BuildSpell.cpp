#include "BuildSpell.h"
#include <cmath>
#include "SpellEvent.h"

BuildSpell::BuildSpell(Context const& c): Spell(c, "box") {
}

void BuildSpell::onEvent(const Event& e) {
  if (e.event_type == EventType::MouseMoved) {
    int x = floor((e.mouse_data.x - m_parent->x()) / m_context.TILE_SIZE);
    int y = floor((e.mouse_data.y - m_parent->y()) / m_context.TILE_SIZE);

    setPosition(x * m_context.TILE_SIZE, y * m_context.TILE_SIZE);
  }
}

void BuildSpell::tick(float dt) {
}

void BuildSpell::cast(std::pair<int, int> from, std::pair<int, int> to) {
  dispatchEvent(new SpellEvent(SpellType::build_wall, floor(m_x /m_context.TILE_SIZE), floor(m_y / m_context.TILE_SIZE)), this);
}
