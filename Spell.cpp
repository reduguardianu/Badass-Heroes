#include "Spell.h"
#include "Utils.h"

Spell::Spell(Context const& c, std::string textureName):AnimatedSprite(c, textureName) {
}

void Spell::cast(std::pair<int, int> from, std::pair<int, int> to) {
  m_x = from.first * m_context.TILE_SIZE;
  m_y = from.second * m_context.TILE_SIZE;

  m_from = from;
  m_to = to;
  animate(Animations::idle);
}

void Spell::tick(float dt) {
  point diff = Utils::getPositionDiff(point(m_x, m_y), point(m_to.first * m_context.TILE_SIZE, m_to.second * m_context.TILE_SIZE), dt);  
  m_x += diff.first;
  m_y += diff.second;
}
